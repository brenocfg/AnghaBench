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
struct att_counter_set {int /*<<< orphan*/  flags_list; int /*<<< orphan*/  mode_list; int /*<<< orphan*/  gid_list; int /*<<< orphan*/  uid_list; } ;
struct mtree_writer {struct att_counter_set acs; } ;

/* Variables and functions */
 int /*<<< orphan*/  attr_counter_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
attr_counter_set_free(struct mtree_writer *mtree)
{
	struct att_counter_set *acs = &mtree->acs;

	attr_counter_free(&acs->uid_list);
	attr_counter_free(&acs->gid_list);
	attr_counter_free(&acs->mode_list);
	attr_counter_free(&acs->flags_list);
}