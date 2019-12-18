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
typedef  int u_int32_t ;
typedef  scalar_t__ time_t ;
struct twe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int TWE_STATUS (struct twe_softc*) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 scalar_t__ time_second ; 

__attribute__((used)) static int
twe_wait_status(struct twe_softc *sc, u_int32_t status, int timeout)
{
    time_t	expiry;
    u_int32_t	status_reg;

    debug_called(4);

    expiry = time_second + timeout;

    do {
	status_reg = TWE_STATUS(sc);
	if (status_reg & status)	/* got the required bit(s)? */
	    return(0);
	DELAY(100000);
    } while (time_second <= expiry);

    return(1);
}