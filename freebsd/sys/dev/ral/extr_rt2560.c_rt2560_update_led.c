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
typedef  int uint32_t ;
struct rt2560_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RAL_WRITE (struct rt2560_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RT2560_LEDCSR ; 

__attribute__((used)) static void
rt2560_update_led(struct rt2560_softc *sc, int led1, int led2)
{
	uint32_t tmp;

	/* set ON period to 70ms and OFF period to 30ms */
	tmp = led1 << 16 | led2 << 17 | 70 << 8 | 30;
	RAL_WRITE(sc, RT2560_LEDCSR, tmp);
}