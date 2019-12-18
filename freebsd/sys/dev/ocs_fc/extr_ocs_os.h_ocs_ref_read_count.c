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
struct TYPE_3__ {int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ ocs_ref_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline uint32_t
ocs_ref_read_count(ocs_ref_t *ref)
{
	return ocs_atomic_read(&ref->count);
}