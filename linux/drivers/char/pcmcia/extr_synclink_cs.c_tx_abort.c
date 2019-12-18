#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ mode; } ;
struct TYPE_5__ {int tx_aborting; int /*<<< orphan*/  lock; scalar_t__ tx_get; scalar_t__ tx_put; scalar_t__ tx_count; TYPE_1__ params; scalar_t__ tx_active; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_2__ MGSLPC_INFO ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 scalar_t__ MGSL_MODE_HDLC ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int tx_abort(MGSLPC_INFO * info)
{
	unsigned long flags;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("tx_abort(%s)\n", info->device_name);

	spin_lock_irqsave(&info->lock, flags);
	if (info->tx_active && info->tx_count &&
	    info->params.mode == MGSL_MODE_HDLC) {
		/* clear data count so FIFO is not filled on next IRQ.
		 * This results in underrun and abort transmission.
		 */
		info->tx_count = info->tx_put = info->tx_get = 0;
		info->tx_aborting = true;
	}
	spin_unlock_irqrestore(&info->lock, flags);
	return 0;
}