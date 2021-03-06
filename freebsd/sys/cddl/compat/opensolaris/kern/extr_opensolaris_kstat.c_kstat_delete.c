#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ks_sysctl_ctx; } ;
typedef  TYPE_1__ kstat_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_KSTAT ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 

void
kstat_delete(kstat_t *ksp)
{

	sysctl_ctx_free(&ksp->ks_sysctl_ctx);
	free(ksp, M_KSTAT);
}