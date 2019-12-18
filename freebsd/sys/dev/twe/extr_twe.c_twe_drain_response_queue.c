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
struct twe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  TWE_Response_Queue ;

/* Variables and functions */
 int /*<<< orphan*/  TWE_RESPONSE_QUEUE (struct twe_softc*) ; 
 int TWE_STATUS (struct twe_softc*) ; 
 int TWE_STATUS_RESPONSE_QUEUE_EMPTY ; 
 int /*<<< orphan*/  debug_called (int) ; 
 scalar_t__ twe_check_bits (struct twe_softc*,int) ; 

__attribute__((used)) static int
twe_drain_response_queue(struct twe_softc *sc)
{
    TWE_Response_Queue	rq;
    u_int32_t		status_reg;

    debug_called(4);

    for (;;) {				/* XXX give up eventually? */
	status_reg = TWE_STATUS(sc);
	if (twe_check_bits(sc, status_reg))
	    return(1);
	if (status_reg & TWE_STATUS_RESPONSE_QUEUE_EMPTY)
	    return(0);
	rq = TWE_RESPONSE_QUEUE(sc);
    }
}