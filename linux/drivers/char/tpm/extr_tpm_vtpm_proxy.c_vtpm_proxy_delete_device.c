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
struct proxy_dev {int state; int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int STATE_REGISTERED_FLAG ; 
 int /*<<< orphan*/  tpm_chip_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtpm_proxy_delete_proxy_dev (struct proxy_dev*) ; 
 int /*<<< orphan*/  vtpm_proxy_fops_undo_open (struct proxy_dev*) ; 
 int /*<<< orphan*/  vtpm_proxy_work_stop (struct proxy_dev*) ; 

__attribute__((used)) static void vtpm_proxy_delete_device(struct proxy_dev *proxy_dev)
{
	vtpm_proxy_work_stop(proxy_dev);

	/*
	 * A client may hold the 'ops' lock, so let it know that the server
	 * side shuts down before we try to grab the 'ops' lock when
	 * unregistering the chip.
	 */
	vtpm_proxy_fops_undo_open(proxy_dev);

	if (proxy_dev->state & STATE_REGISTERED_FLAG)
		tpm_chip_unregister(proxy_dev->chip);

	vtpm_proxy_delete_proxy_dev(proxy_dev);
}