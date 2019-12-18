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
 int /*<<< orphan*/  outw (int,int) ; 

__attribute__((used)) static inline void
noritake_update_irq_hw(int irq, int mask)
{
	int port = 0x54a;
	if (irq >= 32) {
	    mask >>= 16;
	    port = 0x54c;
	}
	outw(mask, port);
}