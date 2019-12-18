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
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_3__ {int /*<<< orphan*/  dthpv_provname; } ;
typedef  TYPE_1__ dtrace_helper_provdesc_t ;

/* Variables and functions */
 int /*<<< orphan*/  fasttrap_provider_retire (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
fasttrap_meta_remove(void *arg, dtrace_helper_provdesc_t *dhpv, pid_t pid)
{
	/*
	 * Clean up the USDT provider. There may be active consumers of the
	 * provider busy adding probes, no damage will actually befall the
	 * provider until that count has dropped to zero. This just puts
	 * the provider on death row.
	 */
	fasttrap_provider_retire(pid, dhpv->dthpv_provname, 1);
}