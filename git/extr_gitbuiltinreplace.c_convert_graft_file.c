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
struct strbuf {char* buf; int /*<<< orphan*/  len; } ;
struct argv_array {int /*<<< orphan*/  argv; scalar_t__ argc; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 scalar_t__ EOF ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ advice_graft_file_deprecated ; 
 int /*<<< orphan*/  argv_array_clear (struct argv_array*) ; 
 int /*<<< orphan*/  argv_array_split (struct argv_array*,char*) ; 
 scalar_t__ create_graft (scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen_or_warn (char const*,char*) ; 
 char* get_graft_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char*) ; 
 scalar_t__ strbuf_getline (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  the_repository ; 
 int unlink_or_warn (char const*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int convert_graft_file(int force)
{
	const char *graft_file = get_graft_file(the_repository);
	FILE *fp = fopen_or_warn(graft_file, "r");
	struct strbuf buf = STRBUF_INIT, err = STRBUF_INIT;
	struct argv_array args = ARGV_ARRAY_INIT;

	if (!fp)
		return -1;

	advice_graft_file_deprecated = 0;
	while (strbuf_getline(&buf, fp) != EOF) {
		if (*buf.buf == '#')
			continue;

		argv_array_split(&args, buf.buf);
		if (args.argc && create_graft(args.argc, args.argv, force, 1))
			strbuf_addf(&err, "\n\t%s", buf.buf);
		argv_array_clear(&args);
	}
	fclose(fp);

	strbuf_release(&buf);

	if (!err.len)
		return unlink_or_warn(graft_file);

	warning(_("could not convert the following graft(s):\n%s"), err.buf);
	strbuf_release(&err);

	return -1;
}