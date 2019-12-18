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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int AUXIO_AUX1_MASK ; 
 int /*<<< orphan*/  auxio_lock ; 
 scalar_t__ auxio_register ; 
 scalar_t__ readl (scalar_t__) ; 
 int sbus_readb (scalar_t__) ; 
 int /*<<< orphan*/  sbus_writeb (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void __auxio_rmw(u8 bits_on, u8 bits_off, int ebus)
{
	if (auxio_register) {
		unsigned long flags;
		u8 regval, newval;

		spin_lock_irqsave(&auxio_lock, flags);

		regval = (ebus ?
			  (u8) readl(auxio_register) :
			  sbus_readb(auxio_register));
		newval =  regval | bits_on;
		newval &= ~bits_off;
		if (!ebus)
			newval &= ~AUXIO_AUX1_MASK;
		if (ebus)
			writel((u32) newval, auxio_register);
		else
			sbus_writeb(newval, auxio_register);
		
		spin_unlock_irqrestore(&auxio_lock, flags);
	}
}