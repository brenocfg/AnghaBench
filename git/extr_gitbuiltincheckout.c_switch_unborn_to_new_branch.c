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
struct checkout_opts {char* new_branch; int /*<<< orphan*/  quiet; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 char* _ (char*) ; 
 int create_symref (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  trace2_cmd_mode (char*) ; 

__attribute__((used)) static int switch_unborn_to_new_branch(const struct checkout_opts *opts)
{
	int status;
	struct strbuf branch_ref = STRBUF_INIT;

	trace2_cmd_mode("unborn");

	if (!opts->new_branch)
		die(_("You are on a branch yet to be born"));
	strbuf_addf(&branch_ref, "refs/heads/%s", opts->new_branch);
	status = create_symref("HEAD", branch_ref.buf, "checkout -b");
	strbuf_release(&branch_ref);
	if (!opts->quiet)
		fprintf(stderr, _("Switched to a new branch '%s'\n"),
			opts->new_branch);
	return status;
}