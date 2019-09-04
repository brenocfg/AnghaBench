#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int count; int /*<<< orphan*/ * ids; } ;
typedef  TYPE_1__ git_oidarray ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void git_oidarray__reverse(git_oidarray *arr)
{
	size_t i;
	git_oid tmp;

	for (i = 0; i < arr->count / 2; i++) {
		git_oid_cpy(&tmp, &arr->ids[i]);
		git_oid_cpy(&arr->ids[i], &arr->ids[(arr->count-1)-i]);
		git_oid_cpy(&arr->ids[(arr->count-1)-i], &tmp);
	}
}