#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct strbuf {int /*<<< orphan*/  buf; } ;
struct remote {char const** url; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ EOF ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  die (char*) ; 
 scalar_t__ do_command (struct strbuf*) ; 
 int dump_from_file ; 
 int /*<<< orphan*/  end_url_with_slash (struct strbuf*,char const*) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_git_dir () ; 
 int /*<<< orphan*/  marksfilename ; 
 int /*<<< orphan*/  notes_ref ; 
 int /*<<< orphan*/  private_ref ; 
 struct remote* remote_get (char const*) ; 
 int /*<<< orphan*/  setup_git_directory () ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ strbuf_getline_lf (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  url ; 
 int /*<<< orphan*/  url_decode (char const*) ; 
 int /*<<< orphan*/  usage (char*) ; 

int cmd_main(int argc, const char **argv)
{
	struct strbuf buf = STRBUF_INIT, url_sb = STRBUF_INIT,
			private_ref_sb = STRBUF_INIT, marksfilename_sb = STRBUF_INIT,
			notes_ref_sb = STRBUF_INIT;
	static struct remote *remote;
	const char *url_in;

	setup_git_directory();
	if (argc < 2 || argc > 3) {
		usage("git-remote-svn <remote-name> [<url>]");
		return 1;
	}

	remote = remote_get(argv[1]);
	url_in = (argc == 3) ? argv[2] : remote->url[0];

	if (starts_with(url_in, "file://")) {
		dump_from_file = 1;
		url = url_decode(url_in + sizeof("file://")-1);
	} else {
		dump_from_file = 0;
		end_url_with_slash(&url_sb, url_in);
		url = url_sb.buf;
	}

	strbuf_addf(&private_ref_sb, "refs/svn/%s/master", remote->name);
	private_ref = private_ref_sb.buf;

	strbuf_addf(&notes_ref_sb, "refs/notes/%s/revs", remote->name);
	notes_ref = notes_ref_sb.buf;

	strbuf_addf(&marksfilename_sb, "%s/info/fast-import/remote-svn/%s.marks",
		get_git_dir(), remote->name);
	marksfilename = marksfilename_sb.buf;

	while (1) {
		if (strbuf_getline_lf(&buf, stdin) == EOF) {
			if (ferror(stdin))
				die("Error reading command stream");
			else
				die("Unexpected end of command stream");
		}
		if (do_command(&buf))
			break;
		strbuf_reset(&buf);
	}

	strbuf_release(&buf);
	strbuf_release(&url_sb);
	strbuf_release(&private_ref_sb);
	strbuf_release(&notes_ref_sb);
	strbuf_release(&marksfilename_sb);
	return 0;
}