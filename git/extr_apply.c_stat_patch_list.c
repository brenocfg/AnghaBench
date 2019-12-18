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
struct patch {scalar_t__ lines_deleted; scalar_t__ lines_added; struct patch* next; } ;
struct apply_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_stat_summary (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  show_stats (struct apply_state*,struct patch*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void stat_patch_list(struct apply_state *state, struct patch *patch)
{
	int files, adds, dels;

	for (files = adds = dels = 0 ; patch ; patch = patch->next) {
		files++;
		adds += patch->lines_added;
		dels += patch->lines_deleted;
		show_stats(state, patch);
	}

	print_stat_summary(stdout, files, adds, dels);
}