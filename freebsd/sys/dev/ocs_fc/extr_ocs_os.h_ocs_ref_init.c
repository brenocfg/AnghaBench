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
struct TYPE_3__ {int /*<<< orphan*/  count; void* arg; int /*<<< orphan*/  release; } ;
typedef  TYPE_1__ ocs_ref_t ;
typedef  int /*<<< orphan*/  ocs_ref_release_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_atomic_init (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void
ocs_ref_init(ocs_ref_t *ref, ocs_ref_release_t release, void *arg)
{
	ref->release = release;
	ref->arg = arg;
	ocs_atomic_init(&ref->count, 1);
}