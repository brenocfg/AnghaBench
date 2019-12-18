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
typedef  scalar_t__ u_int8_t ;
typedef  size_t u_int16_t ;
struct tws_softc {int /*<<< orphan*/  gen_lock; } ;
struct tws_event_packet {scalar_t__ retrieved; } ;
struct tws_circular_q {size_t head; size_t tail; size_t volatile depth; int overflow; scalar_t__ q; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ TWS_AEN_RETRIEVED ; 
 int /*<<< orphan*/  memcpy (struct tws_event_packet*,struct tws_event_packet*,int) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
tws_circular_aenq_insert(struct tws_softc *sc, struct tws_circular_q *cq,
struct tws_event_packet *aen)
{

    struct tws_event_packet *q = (struct tws_event_packet *)cq->q;
    volatile u_int16_t head, tail;
    u_int8_t retr;
    mtx_assert(&sc->gen_lock, MA_OWNED);

    head = cq->head;
    tail = cq->tail;
    retr = q[tail].retrieved;

    memcpy(&q[tail], aen, sizeof(struct tws_event_packet));
    tail = (tail+1) % cq->depth;

    if ( head == tail ) { /* q is full */
        if ( retr != TWS_AEN_RETRIEVED )
            cq->overflow = 1;
        cq->head = (head+1) % cq->depth;
    }
    cq->tail = tail;

}