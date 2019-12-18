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
struct mpu401 {int dummy; } ;

/* Variables and functions */
 unsigned int bus_space_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned char
cmi_mread(struct mpu401 *arg, void *sc, int reg)
{	
	unsigned int d;

		d = bus_space_read_1(0,0, 0x330 + reg); 
	/*	printf("cmi_mread: reg %x %x\n",reg, d);
	*/
	return d;
}