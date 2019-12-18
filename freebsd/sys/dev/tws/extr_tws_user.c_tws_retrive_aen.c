#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
typedef  size_t u_int16_t ;
struct TYPE_3__ {scalar_t__ head; scalar_t__ tail; size_t depth; scalar_t__ q; scalar_t__ overflow; } ;
struct tws_softc {TYPE_1__ aen_q; } ;
struct TYPE_4__ {void* status; } ;
struct tws_ioctl_packet {struct tws_event_packet* data_buf; TYPE_2__ driver_pkt; } ;
struct tws_event_packet {int /*<<< orphan*/  retrieved; int /*<<< orphan*/  sequence_id; } ;

/* Variables and functions */
 void* TWS_AEN_NO_EVENTS ; 
 void* TWS_AEN_OVERFLOW ; 
 int /*<<< orphan*/  TWS_AEN_RETRIEVED ; 
#define  TWS_IOCTL_GET_FIRST_EVENT 131 
#define  TWS_IOCTL_GET_LAST_EVENT 130 
#define  TWS_IOCTL_GET_NEXT_EVENT 129 
#define  TWS_IOCTL_GET_PREVIOUS_EVENT 128 
 int /*<<< orphan*/  TWS_TRACE_DEBUG (struct tws_softc*,char*,struct tws_softc*,int) ; 
 int /*<<< orphan*/  memcpy (struct tws_event_packet*,struct tws_event_packet*,int) ; 

__attribute__((used)) static void 
tws_retrive_aen(struct tws_softc *sc, u_long cmd, 
                            struct tws_ioctl_packet *ubuf)
{
    u_int16_t index=0;
    struct tws_event_packet eventp, *qp;

    if ( sc->aen_q.head == sc->aen_q.tail ) {
        ubuf->driver_pkt.status = TWS_AEN_NO_EVENTS;
        return;
    }
    
    ubuf->driver_pkt.status = 0;

    /* 
     * once this flag is set cli will not display alarms 
     * needs a revisit from tools?
     */
    if ( sc->aen_q.overflow ) {
        ubuf->driver_pkt.status = TWS_AEN_OVERFLOW;
        sc->aen_q.overflow = 0; /* reset */
    }

    qp = (struct tws_event_packet *)sc->aen_q.q;

    switch (cmd) {
        case TWS_IOCTL_GET_FIRST_EVENT :
            index = sc->aen_q.head;
            break;
        case TWS_IOCTL_GET_LAST_EVENT :
            /* index = tail-1 */ 
            index = (sc->aen_q.depth + sc->aen_q.tail - 1) % sc->aen_q.depth;
            break;
        case TWS_IOCTL_GET_NEXT_EVENT :
            memcpy(&eventp, ubuf->data_buf, sizeof(struct tws_event_packet));
            index = sc->aen_q.head;
            do {
                if ( qp[index].sequence_id == 
                           (eventp.sequence_id + 1) )
                    break;
                index  = (index+1) % sc->aen_q.depth;
            }while ( index != sc->aen_q.tail );
            if ( index == sc->aen_q.tail ) {
                ubuf->driver_pkt.status = TWS_AEN_NO_EVENTS;
                return;
            }
            break;
        case TWS_IOCTL_GET_PREVIOUS_EVENT :
            memcpy(&eventp, ubuf->data_buf, sizeof(struct tws_event_packet));
            index = sc->aen_q.head;
            do {
                if ( qp[index].sequence_id == 
                           (eventp.sequence_id - 1) )
                    break;
                index  = (index+1) % sc->aen_q.depth;
            }while ( index != sc->aen_q.tail );
            if ( index == sc->aen_q.tail ) {
                ubuf->driver_pkt.status = TWS_AEN_NO_EVENTS;
                return;
            }
            break;
        default :
            TWS_TRACE_DEBUG(sc, "not a valid event", sc, cmd);
            ubuf->driver_pkt.status = TWS_AEN_NO_EVENTS;
            return;
    }

    memcpy(ubuf->data_buf, &qp[index], 
                           sizeof(struct tws_event_packet));
    qp[index].retrieved = TWS_AEN_RETRIEVED;

    return;

}