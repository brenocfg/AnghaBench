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
struct nitrox_device {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __NDEV_NOT_READY ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nitrox_common_sw_cleanup (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_crypto_unregister () ; 
 int /*<<< orphan*/  nitrox_unregister_interrupts (struct nitrox_device*) ; 

__attribute__((used)) static void nitrox_pf_cleanup(struct nitrox_device *ndev)
{
	 /* PF has no queues in SR-IOV mode */
	atomic_set(&ndev->state, __NDEV_NOT_READY);
	/* unregister crypto algorithms */
	nitrox_crypto_unregister();

	/* cleanup PF resources */
	nitrox_unregister_interrupts(ndev);
	nitrox_common_sw_cleanup(ndev);
}