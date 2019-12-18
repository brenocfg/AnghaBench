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

/* Variables and functions */
 int /*<<< orphan*/  kh_put_oid_set (int /*<<< orphan*/ *,struct object_id const,int*) ; 

int oidset_insert(struct oidset *set, const struct object_id *oid)
{
	int added;
	kh_put_oid_set(&set->set, *oid, &added);
	return !added;
}