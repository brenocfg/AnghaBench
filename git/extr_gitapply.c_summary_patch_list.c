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
struct patch {char* new_name; char* old_name; int score; scalar_t__ is_copy; scalar_t__ is_rename; int /*<<< orphan*/  old_mode; scalar_t__ is_delete; int /*<<< orphan*/  new_mode; scalar_t__ is_new; struct patch* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 int /*<<< orphan*/  show_file_mode_name (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  show_mode_change (struct patch*,int) ; 
 int /*<<< orphan*/  show_rename_copy (struct patch*) ; 

__attribute__((used)) static void summary_patch_list(struct patch *patch)
{
	struct patch *p;

	for (p = patch; p; p = p->next) {
		if (p->is_new)
			show_file_mode_name("create", p->new_mode, p->new_name);
		else if (p->is_delete)
			show_file_mode_name("delete", p->old_mode, p->old_name);
		else {
			if (p->is_rename || p->is_copy)
				show_rename_copy(p);
			else {
				if (p->score) {
					printf(" rewrite %s (%d%%)\n",
					       p->new_name, p->score);
					show_mode_change(p, 0);
				}
				else
					show_mode_change(p, 1);
			}
		}
	}
}