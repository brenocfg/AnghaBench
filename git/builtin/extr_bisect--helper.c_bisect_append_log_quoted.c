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
struct strbuf {char* buf; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  git_path_bisect_log () ; 
 int /*<<< orphan*/  sq_quote_argv (struct strbuf*,char const**) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int bisect_append_log_quoted(const char **argv)
{
	int retval = 0;
	FILE *fp = fopen(git_path_bisect_log(), "a");
	struct strbuf orig_args = STRBUF_INIT;

	if (!fp)
		return -1;

	if (fprintf(fp, "git bisect start") < 1) {
		retval = -1;
		goto finish;
	}

	sq_quote_argv(&orig_args, argv);
	if (fprintf(fp, "%s\n", orig_args.buf) < 1)
		retval = -1;

finish:
	fclose(fp);
	strbuf_release(&orig_args);
	return retval;
}