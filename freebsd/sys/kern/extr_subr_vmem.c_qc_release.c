#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vmem_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  qc_size; int /*<<< orphan*/  qc_vmem; } ;
typedef  TYPE_1__ qcache_t ;

/* Variables and functions */
 int /*<<< orphan*/  vmem_xfree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qc_release(void *arg, void **store, int cnt)
{
	qcache_t *qc;
	int i;

	qc = arg;
	for (i = 0; i < cnt; i++)
		vmem_xfree(qc->qc_vmem, (vmem_addr_t)store[i], qc->qc_size);
}