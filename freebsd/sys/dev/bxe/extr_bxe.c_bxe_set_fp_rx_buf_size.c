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
typedef  int uint32_t ;
struct bxe_softc {int mtu; int num_queues; TYPE_1__* fp; } ;
struct TYPE_2__ {int rx_buf_size; int mbuf_alloc_size; } ;

/* Variables and functions */
 int ETH_OVERHEAD ; 
 int IP_HEADER_ALIGNMENT_PADDING ; 
 int MCLBYTES ; 
 int MJUMPAGESIZE ; 

__attribute__((used)) static void
bxe_set_fp_rx_buf_size(struct bxe_softc *sc)
{
    int i;
    uint32_t rx_buf_size;

    rx_buf_size = (IP_HEADER_ALIGNMENT_PADDING + ETH_OVERHEAD + sc->mtu);

    for (i = 0; i < sc->num_queues; i++) {
        if(rx_buf_size <= MCLBYTES){
            sc->fp[i].rx_buf_size = rx_buf_size;
            sc->fp[i].mbuf_alloc_size = MCLBYTES;
        }else if (rx_buf_size <= MJUMPAGESIZE){
            sc->fp[i].rx_buf_size = rx_buf_size;
            sc->fp[i].mbuf_alloc_size = MJUMPAGESIZE;
        }else if (rx_buf_size <= (MJUMPAGESIZE + MCLBYTES)){
            sc->fp[i].rx_buf_size = MCLBYTES;
            sc->fp[i].mbuf_alloc_size = MCLBYTES;
        }else if (rx_buf_size <= (2 * MJUMPAGESIZE)){
            sc->fp[i].rx_buf_size = MJUMPAGESIZE;
            sc->fp[i].mbuf_alloc_size = MJUMPAGESIZE;
        }else {
            sc->fp[i].rx_buf_size = MCLBYTES;
            sc->fp[i].mbuf_alloc_size = MCLBYTES;
        }
    }
}