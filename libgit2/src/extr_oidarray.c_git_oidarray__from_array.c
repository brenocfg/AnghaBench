#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ids; int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ git_oidarray ;
struct TYPE_6__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  size; } ;
typedef  TYPE_2__ git_array_oid_t ;

/* Variables and functions */

void git_oidarray__from_array(git_oidarray *arr, git_array_oid_t *array)
{
	arr->count = array->size;
	arr->ids = array->ptr;
}