#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct i2s_softc {int dummy; } ;
struct TYPE_2__ {scalar_t__ level; } ;

/* Variables and functions */
 size_t HEADPHONE_DETECT ; 
 size_t LINEOUT_DETECT ; 
 TYPE_1__** gpio_ctrls ; 
 int /*<<< orphan*/  i2s_set_outputs (struct i2s_softc*,int) ; 

__attribute__((used)) static void 
i2s_cint(struct i2s_softc *sc)
{
	u_int mask = 0;

	if (gpio_ctrls[HEADPHONE_DETECT] && 
	    gpio_ctrls[HEADPHONE_DETECT]->level)
		mask |= 1 << 1;

	if (gpio_ctrls[LINEOUT_DETECT] && 
	    gpio_ctrls[LINEOUT_DETECT]->level)
		mask |= 1 << 2;

	if (mask == 0)
		mask = 1 << 0; /* fall back to speakers. */

	i2s_set_outputs(sc, mask);
}