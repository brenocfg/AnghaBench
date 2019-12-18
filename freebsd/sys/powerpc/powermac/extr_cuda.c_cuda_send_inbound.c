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
struct cuda_softc {int sc_autopoll; int /*<<< orphan*/  sc_mutex; int /*<<< orphan*/  sc_freeq; int /*<<< orphan*/  sc_rtc; int /*<<< orphan*/  adb_bus; int /*<<< orphan*/  sc_inq; int /*<<< orphan*/  sc_dev; } ;
struct cuda_packet {int type; int len; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  CMD_AUTOPOLL 133 
#define  CMD_READ_RTC 132 
#define  CMD_WRITE_RTC 131 
#define  CUDA_ADB 130 
#define  CUDA_ERROR 129 
#define  CUDA_PSEUDO 128 
 struct cuda_packet* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct cuda_packet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adb_receive_raw_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pkt_q ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cuda_send_inbound(struct cuda_softc *sc)
{
	device_t dev;
	struct cuda_packet *pkt;

	dev = sc->sc_dev;
	
	mtx_lock(&sc->sc_mutex);

	while ((pkt = STAILQ_FIRST(&sc->sc_inq)) != NULL) {
		STAILQ_REMOVE_HEAD(&sc->sc_inq, pkt_q);

		mtx_unlock(&sc->sc_mutex);

		/* check if we have a handler for this message */
		switch (pkt->type) {
		   case CUDA_ADB:
			if (pkt->len > 2) {
				adb_receive_raw_packet(sc->adb_bus,
				    pkt->data[0],pkt->data[1],
				    pkt->len - 2,&pkt->data[2]);
			} else {
				adb_receive_raw_packet(sc->adb_bus,
				    pkt->data[0],pkt->data[1],0,NULL);
			}
			break;
		   case CUDA_PSEUDO:
			mtx_lock(&sc->sc_mutex);
			switch (pkt->data[1]) {
			case CMD_AUTOPOLL:
				sc->sc_autopoll = 1;
				break;
			case CMD_READ_RTC:
				memcpy(&sc->sc_rtc, &pkt->data[2],
				    sizeof(sc->sc_rtc));
				wakeup(&sc->sc_rtc);
				break;
			case CMD_WRITE_RTC:
				break;
			}
			mtx_unlock(&sc->sc_mutex);
			break;
		   case CUDA_ERROR:
			/*
			 * CUDA will throw errors if we miss a race between
			 * sending and receiving packets. This is already
			 * handled when we abort packet output to handle
			 * this packet in cuda_intr(). Thus, we ignore
			 * these messages.
			 */
			break;
		   default:
			device_printf(dev,"unknown CUDA command %d\n",
			    pkt->type);
			break;
		}

		mtx_lock(&sc->sc_mutex);

		STAILQ_INSERT_TAIL(&sc->sc_freeq, pkt, pkt_q);
	}

	mtx_unlock(&sc->sc_mutex);
}