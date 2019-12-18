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
typedef  int u_int64_t ;
struct tws_softc {int dma_mem_phys; struct tws_sense* sense_bufs; } ;
struct tws_sense {int hdr_pkt_phy; } ;
struct tws_command_packet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWS_TRACE_DEBUG (struct tws_softc*,char*,struct tws_softc*,int) ; 
 int tws_queue_depth ; 

struct tws_sense *
tws_find_sense_from_mfa(struct tws_softc *sc, u_int64_t mfa)
{
    struct tws_sense *s;
    int i;
    TWS_TRACE_DEBUG(sc, "entry",sc,mfa);

    i = (mfa - sc->dma_mem_phys) / sizeof(struct tws_command_packet);
    if ( i>= 0 && i<tws_queue_depth) {
        s = &sc->sense_bufs[i];
        if ( mfa == s->hdr_pkt_phy )
            return(s);
    }

    TWS_TRACE_DEBUG(sc, "return null",0,mfa);
    return(NULL);

}