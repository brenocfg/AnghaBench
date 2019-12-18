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
struct sc_info {int dummy; } ;
struct mpu401 {int dummy; } ;

/* Variables and functions */
 unsigned int emu_rd (struct sc_info*,int,int) ; 

__attribute__((used)) static unsigned char
emu_mread(struct mpu401 *arg, void *sc, int reg)
{	
	unsigned int d;

	d = emu_rd((struct sc_info *)sc, 0x18 + reg, 1); 
	return d;
}