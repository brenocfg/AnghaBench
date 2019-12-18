#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct strbuf {scalar_t__ len; scalar_t__ buf; } ;
struct TYPE_9__ {int verbosity; int progress; int thin; int /*<<< orphan*/  push_options; int /*<<< orphan*/  deepen_not; } ;
struct TYPE_8__ {char const** url; } ;
struct TYPE_7__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 scalar_t__ EOF ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_url_with_slash (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,...) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_refs (int) ; 
 int /*<<< orphan*/  http_cleanup () ; 
 int /*<<< orphan*/  http_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isatty (int) ; 
 TYPE_4__ options ; 
 int /*<<< orphan*/  output_refs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_fetch (struct strbuf*) ; 
 int /*<<< orphan*/  parse_push (struct strbuf*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 TYPE_2__* remote ; 
 TYPE_2__* remote_get (char const*) ; 
 int set_option (char const*,char*) ; 
 int /*<<< orphan*/  setup_git_directory_gently (int*) ; 
 scalar_t__ skip_prefix (scalar_t__,char*,char const**) ; 
 scalar_t__ starts_with (scalar_t__,char*) ; 
 int /*<<< orphan*/  stateless_connect (char const*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strbuf_getline_lf (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char*) ; 
 int /*<<< orphan*/  string_list_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strstr (scalar_t__,char*) ; 
 int /*<<< orphan*/  trace2_cmd_name (char*) ; 
 TYPE_1__ url ; 

int cmd_main(int argc, const char **argv)
{
	struct strbuf buf = STRBUF_INIT;
	int nongit;

	setup_git_directory_gently(&nongit);
	if (argc < 2) {
		error(_("remote-curl: usage: git remote-curl <remote> [<url>]"));
		return 1;
	}

	options.verbosity = 1;
	options.progress = !!isatty(2);
	options.thin = 1;
	string_list_init(&options.deepen_not, 1);
	string_list_init(&options.push_options, 1);

	/*
	 * Just report "remote-curl" here (folding all the various aliases
	 * ("git-remote-http", "git-remote-https", and etc.) here since they
	 * are all just copies of the same actual executable.
	 */
	trace2_cmd_name("remote-curl");

	remote = remote_get(argv[1]);

	if (argc > 2) {
		end_url_with_slash(&url, argv[2]);
	} else {
		end_url_with_slash(&url, remote->url[0]);
	}

	http_init(remote, url.buf, 0);

	do {
		const char *arg;

		if (strbuf_getline_lf(&buf, stdin) == EOF) {
			if (ferror(stdin))
				error(_("remote-curl: error reading command stream from git"));
			return 1;
		}
		if (buf.len == 0)
			break;
		if (starts_with(buf.buf, "fetch ")) {
			if (nongit)
				die(_("remote-curl: fetch attempted without a local repo"));
			parse_fetch(&buf);

		} else if (!strcmp(buf.buf, "list") || starts_with(buf.buf, "list ")) {
			int for_push = !!strstr(buf.buf + 4, "for-push");
			output_refs(get_refs(for_push));

		} else if (starts_with(buf.buf, "push ")) {
			parse_push(&buf);

		} else if (skip_prefix(buf.buf, "option ", &arg)) {
			char *value = strchr(arg, ' ');
			int result;

			if (value)
				*value++ = '\0';
			else
				value = "true";

			result = set_option(arg, value);
			if (!result)
				printf("ok\n");
			else if (result < 0)
				printf("error invalid value\n");
			else
				printf("unsupported\n");
			fflush(stdout);

		} else if (!strcmp(buf.buf, "capabilities")) {
			printf("stateless-connect\n");
			printf("fetch\n");
			printf("option\n");
			printf("push\n");
			printf("check-connectivity\n");
			printf("\n");
			fflush(stdout);
		} else if (skip_prefix(buf.buf, "stateless-connect ", &arg)) {
			if (!stateless_connect(arg))
				break;
		} else {
			error(_("remote-curl: unknown command '%s' from git"), buf.buf);
			return 1;
		}
		strbuf_reset(&buf);
	} while (1);

	http_cleanup();

	return 0;
}