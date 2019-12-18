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
 unsigned int VME_MAX_SOURCES ; 
 unsigned int VME_SOURCE_BASE ; 
 int free_vme_vec_bitmap ; 

void atari_unregister_vme_int(unsigned int irq)
{
	if (irq >= VME_SOURCE_BASE && irq < VME_SOURCE_BASE + VME_MAX_SOURCES) {
		irq -= VME_SOURCE_BASE;
		free_vme_vec_bitmap &= ~(1 << irq);
	}
}