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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ppb_data* DEVTOSOFTC (int /*<<< orphan*/ ) ; 
 int mtx_sleep (void*,int /*<<< orphan*/ ,int,char const*,int) ; 

int
ppb_sleep(device_t bus, void *wchan, int priority, const char *wmesg, int timo)
{
	struct ppb_data *ppb = DEVTOSOFTC(bus);

	return (mtx_sleep(wchan, ppb->ppc_lock, priority, wmesg, timo));
}