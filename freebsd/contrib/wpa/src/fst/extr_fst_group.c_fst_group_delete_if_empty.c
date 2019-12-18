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
struct fst_group {int dummy; } ;
typedef  int Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  fst_group_delete (struct fst_group*) ; 
 int /*<<< orphan*/  fst_group_has_ifaces (struct fst_group*) ; 
 int /*<<< orphan*/  fst_session_global_get_first_by_group (struct fst_group*) ; 

Boolean fst_group_delete_if_empty(struct fst_group *group)
{
	Boolean is_empty = !fst_group_has_ifaces(group) &&
		!fst_session_global_get_first_by_group(group);

	if (is_empty)
		fst_group_delete(group);

	return is_empty;
}