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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  entry_count; } ;
typedef  TYPE_1__ ocs_varray_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 

uint32_t
ocs_varray_get_count(ocs_varray_t *va)
{
	uint32_t rc;

	ocs_lock(&va->lock);
		rc = va->entry_count;
	ocs_unlock(&va->lock);
	return rc;
}