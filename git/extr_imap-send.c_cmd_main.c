#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct strbuf {scalar_t__ len; } ;
struct TYPE_4__ {int port; char* host; scalar_t__ tunnel; int /*<<< orphan*/  folder; scalar_t__ use_ssl; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int append_msgs_to_imap (TYPE_1__*,struct strbuf*,int) ; 
 int count_messages (struct strbuf*) ; 
 int curl_append_msgs_to_imap (TYPE_1__*,struct strbuf*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_imap_config () ; 
 int /*<<< orphan*/  imap_send_options ; 
 int /*<<< orphan*/  imap_send_usage ; 
 int parse_options (int,char const**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ read_message (int /*<<< orphan*/ ,struct strbuf*) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  setup_git_directory_gently (int*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int use_curl ; 
 int /*<<< orphan*/  warning (char*) ; 

int cmd_main(int argc, const char **argv)
{
	struct strbuf all_msgs = STRBUF_INIT;
	int total;
	int nongit_ok;

	setup_git_directory_gently(&nongit_ok);
	git_imap_config();

	argc = parse_options(argc, (const char **)argv, "", imap_send_options, imap_send_usage, 0);

	if (argc)
		usage_with_options(imap_send_usage, imap_send_options);

#ifndef USE_CURL_FOR_IMAP_SEND
	if (use_curl) {
		warning("--curl not supported in this build");
		use_curl = 0;
	}
#elif defined(NO_OPENSSL)
	if (!use_curl) {
		warning("--no-curl not supported in this build");
		use_curl = 1;
	}
#endif

	if (!server.port)
		server.port = server.use_ssl ? 993 : 143;

	if (!server.folder) {
		fprintf(stderr, "no imap store specified\n");
		return 1;
	}
	if (!server.host) {
		if (!server.tunnel) {
			fprintf(stderr, "no imap host specified\n");
			return 1;
		}
		server.host = "tunnel";
	}

	/* read the messages */
	if (read_message(stdin, &all_msgs)) {
		fprintf(stderr, "error reading input\n");
		return 1;
	}

	if (all_msgs.len == 0) {
		fprintf(stderr, "nothing to send\n");
		return 1;
	}

	total = count_messages(&all_msgs);
	if (!total) {
		fprintf(stderr, "no messages to send\n");
		return 1;
	}

	/* write it to the imap server */

	if (server.tunnel)
		return append_msgs_to_imap(&server, &all_msgs, total);

#ifdef USE_CURL_FOR_IMAP_SEND
	if (use_curl)
		return curl_append_msgs_to_imap(&server, &all_msgs, total);
#endif

	return append_msgs_to_imap(&server, &all_msgs, total);
}