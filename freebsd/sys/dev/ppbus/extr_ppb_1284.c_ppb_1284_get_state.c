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
struct ppb_data {int state; int /*<<< orphan*/  ppc_lock; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ppb_data* DEVTOSOFTC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ppb_1284_get_state(device_t bus)
{
	struct ppb_data *ppb = DEVTOSOFTC(bus);

	mtx_assert(ppb->ppc_lock, MA_OWNED);
	return (ppb->state);
}