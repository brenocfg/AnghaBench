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
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* release ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ ocs_ref_t ;

/* Variables and functions */
 int ocs_atomic_sub_return (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint32_t
ocs_ref_put(ocs_ref_t *ref)
{
	uint32_t rc = 0;
	if (ocs_atomic_sub_return(&ref->count, 1) == 1) {
		ref->release(ref->arg);
		rc = 1;
	}
	return rc;
}