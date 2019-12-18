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
struct malo_hal {int mh_imask; int /*<<< orphan*/  mh_ioh; int /*<<< orphan*/  mh_iot; } ;

/* Variables and functions */
 int /*<<< orphan*/  MALO_REG_A2H_INTERRUPT_CAUSE ; 
 int /*<<< orphan*/  MALO_REG_INT_CODE ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
malo_hal_getisr(struct malo_hal *mh, uint32_t *status)
{
	uint32_t cause;

	cause = bus_space_read_4(mh->mh_iot, mh->mh_ioh,
	    MALO_REG_A2H_INTERRUPT_CAUSE);
	if (cause == 0xffffffff) {	/* card removed */
		cause = 0;
	} else if (cause != 0) {
		/* clear cause bits */
		bus_space_write_4(mh->mh_iot, mh->mh_ioh,
		    MALO_REG_A2H_INTERRUPT_CAUSE, cause &~ mh->mh_imask);
		(void) bus_space_read_4(mh->mh_iot, mh->mh_ioh,
		    MALO_REG_INT_CODE);
		cause &= mh->mh_imask;
	}

	*status = cause;
}