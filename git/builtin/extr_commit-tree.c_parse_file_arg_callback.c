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
struct strbuf {scalar_t__ len; } ;
struct option {struct strbuf* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON_OPT_NEG_NOARG (int,char const*) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,char const*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 scalar_t__ strbuf_read (struct strbuf*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int parse_file_arg_callback(const struct option *opt,
		const char *arg, int unset)
{
	int fd;
	struct strbuf *buf = opt->value;

	BUG_ON_OPT_NEG_NOARG(unset, arg);

	if (buf->len)
		strbuf_addch(buf, '\n');
	if (!strcmp(arg, "-"))
		fd = 0;
	else {
		fd = open(arg, O_RDONLY);
		if (fd < 0)
			die_errno(_("git commit-tree: failed to open '%s'"), arg);
	}
	if (strbuf_read(buf, fd, 0) < 0)
		die_errno(_("git commit-tree: failed to read '%s'"), arg);
	if (fd && close(fd))
		die_errno(_("git commit-tree: failed to close '%s'"), arg);

	return 0;
}