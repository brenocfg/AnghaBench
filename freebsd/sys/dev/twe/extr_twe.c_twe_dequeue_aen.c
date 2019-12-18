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
typedef  int /*<<< orphan*/  u_int16_t ;
struct twe_softc {size_t twe_aen_tail; size_t twe_aen_head; int /*<<< orphan*/ * twe_aen_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWE_AEN_QUEUE_EMPTY ; 
 int /*<<< orphan*/  TWE_IO_ASSERT_LOCKED (struct twe_softc*) ; 
 int TWE_Q_LENGTH ; 
 int /*<<< orphan*/  debug_called (int) ; 

__attribute__((used)) static u_int16_t
twe_dequeue_aen(struct twe_softc *sc)
{
    u_int16_t	result;
    
    debug_called(4);

    TWE_IO_ASSERT_LOCKED(sc);
    if (sc->twe_aen_tail == sc->twe_aen_head) {
	result = TWE_AEN_QUEUE_EMPTY;
    } else {
	result = sc->twe_aen_queue[sc->twe_aen_tail];
	sc->twe_aen_tail = ((sc->twe_aen_tail + 1) % TWE_Q_LENGTH);
    }
    return(result);
}