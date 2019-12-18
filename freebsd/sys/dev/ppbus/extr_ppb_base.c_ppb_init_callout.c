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
struct ppb_data {int /*<<< orphan*/  ppc_lock; } ;
struct callout {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ppb_data* DEVTOSOFTC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_init_mtx (struct callout*,int /*<<< orphan*/ ,int) ; 

void
ppb_init_callout(device_t bus, struct callout *c, int flags)
{
	struct ppb_data *ppb = DEVTOSOFTC(bus);

	callout_init_mtx(c, ppb->ppc_lock, flags);
}