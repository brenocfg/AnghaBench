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
 int /*<<< orphan*/  WRITE_RWA (int,int) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int inb (int) ; 

__attribute__((used)) static inline void rwa010_soundblaster_init(int sb_base, int al_base, int irq, int dma)
{
	int i;

	WRITE_RWA(7, 1);

	dprintk("SoundBlaster base: ");
	WRITE_RWA(0x61, sb_base & 255);
	i = inb(0x203);

	WRITE_RWA(0x60, sb_base >> 8);
	dprintk("%02X%02X (%X),", inb(0x203), i, sb_base);

	dprintk(" irq: ");
	WRITE_RWA(0x70, irq);
	dprintk("%d (%d),", inb(0x203), irq);

	dprintk(" 8-bit DMA: ");
	WRITE_RWA(0x74, dma);
	dprintk("%d (%d)\n", inb(0x203), dma);

	dprintk("AdLib base: ");
	WRITE_RWA(0x63, al_base & 255);
	i = inb(0x203);

	WRITE_RWA(0x62, al_base >> 8);
	dprintk("%02X%02X (%X)\n", inb(0x203), i, al_base);

	WRITE_RWA(0x30, 1);
}