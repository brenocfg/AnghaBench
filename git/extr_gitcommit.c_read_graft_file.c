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
struct repository {int dummy; } ;
struct commit_graft {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ advice_graft_file_deprecated ; 
 int /*<<< orphan*/  advise (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen_or_warn (char const*,char*) ; 
 struct commit_graft* read_graft_line (struct strbuf*) ; 
 scalar_t__ register_commit_graft (struct repository*,struct commit_graft*,int) ; 
 int /*<<< orphan*/  strbuf_getwholeline (struct strbuf*,int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int read_graft_file(struct repository *r, const char *graft_file)
{
	FILE *fp = fopen_or_warn(graft_file, "r");
	struct strbuf buf = STRBUF_INIT;
	if (!fp)
		return -1;
	if (advice_graft_file_deprecated)
		advise(_("Support for <GIT_DIR>/info/grafts is deprecated\n"
			 "and will be removed in a future Git version.\n"
			 "\n"
			 "Please use \"git replace --convert-graft-file\"\n"
			 "to convert the grafts into replace refs.\n"
			 "\n"
			 "Turn this message off by running\n"
			 "\"git config advice.graftFileDeprecated false\""));
	while (!strbuf_getwholeline(&buf, fp, '\n')) {
		/* The format is just "Commit Parent1 Parent2 ...\n" */
		struct commit_graft *graft = read_graft_line(&buf);
		if (!graft)
			continue;
		if (register_commit_graft(r, graft, 1))
			error("duplicate graft data: %s", buf.buf);
	}
	fclose(fp);
	strbuf_release(&buf);
	return 0;
}