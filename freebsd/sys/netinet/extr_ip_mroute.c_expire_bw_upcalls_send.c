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
struct vnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BW_UPCALLS_PERIOD ; 
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (struct vnet*) ; 
 int /*<<< orphan*/  MFC_LOCK () ; 
 int /*<<< orphan*/  MFC_UNLOCK () ; 
 int /*<<< orphan*/  V_bw_upcalls_ch ; 
 int /*<<< orphan*/  bw_upcalls_send () ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curvnet ; 

__attribute__((used)) static void
expire_bw_upcalls_send(void *arg)
{
    CURVNET_SET((struct vnet *) arg);

    MFC_LOCK();
    bw_upcalls_send();
    MFC_UNLOCK();

    callout_reset(&V_bw_upcalls_ch, BW_UPCALLS_PERIOD, expire_bw_upcalls_send,
	curvnet);
    CURVNET_RESTORE();
}