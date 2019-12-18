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
typedef  scalar_t__ u_int32_t ;
struct mrsas_softc {scalar_t__ is_aero; } ;

/* Variables and functions */
 scalar_t__ mrsas_read_reg (struct mrsas_softc*,int) ; 

u_int32_t
mrsas_read_reg_with_retries(struct mrsas_softc *sc, int offset)
{
	u_int32_t i = 0, ret_val;

	if (sc->is_aero) {
		do {
			ret_val = mrsas_read_reg(sc, offset);
			i++;
		} while(ret_val == 0 && i < 3);
	} else
		ret_val = mrsas_read_reg(sc, offset);

	return ret_val;
}