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
struct oidset {int /*<<< orphan*/  set; } ;
struct object_id {int dummy; } ;
typedef  scalar_t__ khiter_t ;

/* Variables and functions */
 int /*<<< orphan*/  kh_del_oid_set (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ kh_end (int /*<<< orphan*/ *) ; 
 scalar_t__ kh_get_oid_set (int /*<<< orphan*/ *,struct object_id const) ; 

int oidset_remove(struct oidset *set, const struct object_id *oid)
{
	khiter_t pos = kh_get_oid_set(&set->set, *oid);
	if (pos == kh_end(&set->set))
		return 0;
	kh_del_oid_set(&set->set, pos);
	return 1;
}