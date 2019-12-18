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
typedef  int uint8_t ;
struct ppb_data {int /*<<< orphan*/  ppc_lock; } ;
typedef  scalar_t__ device_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 struct ppb_data* DEVTOSOFTC (scalar_t__) ; 
 int EWOULDBLOCK ; 
 int PCATCH ; 
 int PPBPRI ; 
 int PPB_FOREVER ; 
 int PPB_NOINTR ; 
 int PPB_POLL ; 
 int hz ; 
 int mtx_sleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  ppb_assert_locked (scalar_t__) ; 
 int ppb_rstr (scalar_t__) ; 

int
ppb_poll_bus(device_t bus, int max,
	     uint8_t mask, uint8_t status, int how)
{
	struct ppb_data *ppb = DEVTOSOFTC(bus);
	int i, j, error;
	uint8_t r;

	ppb_assert_locked(bus);

	/* try at least up to 10ms */
	for (j = 0; j < ((how & PPB_POLL) ? max : 1); j++) {
		for (i = 0; i < 10000; i++) {
			r = ppb_rstr(bus);
			DELAY(1);
			if ((r & mask) == status)
				return (0);
		}
	}

	if (!(how & PPB_POLL)) {
	   for (i = 0; max == PPB_FOREVER || i < max-1; i++) {
		if ((ppb_rstr(bus) & mask) == status)
			return (0);

		/* wait 10 ms */
		error = mtx_sleep((caddr_t)bus, ppb->ppc_lock, PPBPRI |
		    (how == PPB_NOINTR ? 0 : PCATCH), "ppbpoll", hz/100);
		if (error != EWOULDBLOCK)
			return (error);
	   }
	}

	return (EWOULDBLOCK);
}