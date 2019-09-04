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
struct strbuf {int dummy; } ;
struct commit_graft {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen_or_warn (char const*,char*) ; 
 struct commit_graft* read_graft_line (struct strbuf*) ; 
 int /*<<< orphan*/  register_commit_graft (int /*<<< orphan*/ ,struct commit_graft*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_getwholeline (struct strbuf*,int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int read_ancestry(const char *graft_file)
{
	FILE *fp = fopen_or_warn(graft_file, "r");
	struct strbuf buf = STRBUF_INIT;
	if (!fp)
		return -1;
	while (!strbuf_getwholeline(&buf, fp, '\n')) {
		/* The format is just "Commit Parent1 Parent2 ...\n" */
		struct commit_graft *graft = read_graft_line(&buf);
		if (graft)
			register_commit_graft(the_repository, graft, 0);
	}
	fclose(fp);
	strbuf_release(&buf);
	return 0;
}