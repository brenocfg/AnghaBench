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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  AUXIO_AUX1_LED ; 
 int /*<<< orphan*/  AUXIO_PCIO_LED ; 
 int /*<<< orphan*/  __auxio_rmw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __auxio_set_bit(u8 bit, int on, int ebus)
{
	u8 bits_on = (ebus ? AUXIO_PCIO_LED : AUXIO_AUX1_LED);
	u8 bits_off = 0;

	if (!on) {
		u8 tmp = bits_off;
		bits_off = bits_on;
		bits_on = tmp;
	}
	__auxio_rmw(bits_on, bits_off, ebus);
}