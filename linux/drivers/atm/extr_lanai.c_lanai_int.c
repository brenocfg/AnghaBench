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
typedef  int u32 ;
struct lanai_dev {int conf1; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int CONFIG1_POWERDOWN ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int intr_pending (struct lanai_dev*) ; 
 int /*<<< orphan*/  lanai_int_1 (struct lanai_dev*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t lanai_int(int irq, void *devid)
{
	struct lanai_dev *lanai = devid;
	u32 reason;

#ifdef USE_POWERDOWN
	/*
	 * If we're powered down we shouldn't be generating any interrupts -
	 * so assume that this is a shared interrupt line and it's for someone
	 * else
	 */
	if (unlikely(lanai->conf1 & CONFIG1_POWERDOWN))
		return IRQ_NONE;
#endif

	reason = intr_pending(lanai);
	if (reason == 0)
		return IRQ_NONE;	/* Must be for someone else */

	do {
		if (unlikely(reason == 0xFFFFFFFF))
			break;		/* Maybe we've been unplugged? */
		lanai_int_1(lanai, reason);
		reason = intr_pending(lanai);
	} while (reason != 0);

	return IRQ_HANDLED;
}