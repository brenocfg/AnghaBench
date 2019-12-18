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
typedef  int u_int ;
struct jz4780_pic_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  JZ_ICMSR0 ; 
 int /*<<< orphan*/  JZ_ICMSR1 ; 
 int /*<<< orphan*/  WRITE4 (struct jz4780_pic_softc*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void
pic_irq_mask(struct jz4780_pic_softc *sc, u_int irq)
{
	if (irq < 32)
		WRITE4(sc, JZ_ICMSR0, (1u << irq));
	else
		WRITE4(sc, JZ_ICMSR1, (1u << (irq - 32)));
}