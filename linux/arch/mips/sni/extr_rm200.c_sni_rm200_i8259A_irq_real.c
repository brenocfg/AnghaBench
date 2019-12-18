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

/* Variables and functions */
 scalar_t__ PIC_CMD ; 
 int readb (scalar_t__) ; 
 scalar_t__ rm200_pic_master ; 
 scalar_t__ rm200_pic_slave ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static inline int sni_rm200_i8259A_irq_real(unsigned int irq)
{
	int value;
	int irqmask = 1 << irq;

	if (irq < 8) {
		writeb(0x0B, rm200_pic_master + PIC_CMD);
		value = readb(rm200_pic_master + PIC_CMD) & irqmask;
		writeb(0x0A, rm200_pic_master + PIC_CMD);
		return value;
	}
	writeb(0x0B, rm200_pic_slave + PIC_CMD); /* ISR register */
	value = readb(rm200_pic_slave + PIC_CMD) & (irqmask >> 8);
	writeb(0x0A, rm200_pic_slave + PIC_CMD);
	return value;
}