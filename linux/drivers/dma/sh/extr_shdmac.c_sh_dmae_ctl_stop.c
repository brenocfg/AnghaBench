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
struct sh_dmae_device {int dummy; } ;

/* Variables and functions */
 unsigned short DMAOR_AE ; 
 unsigned short DMAOR_DME ; 
 unsigned short DMAOR_NMIF ; 
 unsigned short dmaor_read (struct sh_dmae_device*) ; 
 int /*<<< orphan*/  dmaor_write (struct sh_dmae_device*,unsigned short) ; 
 int /*<<< orphan*/  sh_dmae_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sh_dmae_ctl_stop(struct sh_dmae_device *shdev)
{
	unsigned short dmaor;
	unsigned long flags;

	spin_lock_irqsave(&sh_dmae_lock, flags);

	dmaor = dmaor_read(shdev);
	dmaor_write(shdev, dmaor & ~(DMAOR_NMIF | DMAOR_AE | DMAOR_DME));

	spin_unlock_irqrestore(&sh_dmae_lock, flags);
}