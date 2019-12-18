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
struct ata_port {int dummy; } ;
struct ata_device {scalar_t__ pio_mode; } ;

/* Variables and functions */
 scalar_t__ XFER_PIO_0 ; 
 int /*<<< orphan*/  atiixp_lock ; 
 int /*<<< orphan*/  atiixp_set_pio_timing (struct ata_port*,struct ata_device*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void atiixp_set_piomode(struct ata_port *ap, struct ata_device *adev)
{
	unsigned long flags;
	spin_lock_irqsave(&atiixp_lock, flags);
	atiixp_set_pio_timing(ap, adev, adev->pio_mode - XFER_PIO_0);
	spin_unlock_irqrestore(&atiixp_lock, flags);
}