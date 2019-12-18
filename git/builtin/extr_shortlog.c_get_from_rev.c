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
struct shortlog {int dummy; } ;
struct rev_info {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 struct commit* get_revision (struct rev_info*) ; 
 scalar_t__ prepare_revision_walk (struct rev_info*) ; 
 int /*<<< orphan*/  shortlog_add_commit (struct shortlog*,struct commit*) ; 

__attribute__((used)) static void get_from_rev(struct rev_info *rev, struct shortlog *log)
{
	struct commit *commit;

	if (prepare_revision_walk(rev))
		die(_("revision walk setup failed"));
	while ((commit = get_revision(rev)) != NULL)
		shortlog_add_commit(log, commit);
}