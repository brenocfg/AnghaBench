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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  allow_rerere_auto ; 
 int /*<<< orphan*/  append_conflicts_hint (int /*<<< orphan*/ *,struct strbuf*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* git_path_merge_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  repo_rerere (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  the_index ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/ * xfopen (char const*,char*) ; 

__attribute__((used)) static int suggest_conflicts(void)
{
	const char *filename;
	FILE *fp;
	struct strbuf msgbuf = STRBUF_INIT;

	filename = git_path_merge_msg(the_repository);
	fp = xfopen(filename, "a");

	append_conflicts_hint(&the_index, &msgbuf);
	fputs(msgbuf.buf, fp);
	strbuf_release(&msgbuf);
	fclose(fp);
	repo_rerere(the_repository, allow_rerere_auto);
	printf(_("Automatic merge failed; "
			"fix conflicts and then commit the result.\n"));
	return 1;
}