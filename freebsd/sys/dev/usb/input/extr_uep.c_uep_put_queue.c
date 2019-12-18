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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_2__ {int /*<<< orphan*/ * fp; } ;
struct uep_softc {TYPE_1__ fifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  UEP_PACKET_LEN_REPORT ; 
 size_t USB_FIFO_RX ; 
 int /*<<< orphan*/  usb_fifo_put_data_linear (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
uep_put_queue(struct uep_softc *sc, u_char *buf)
{
	usb_fifo_put_data_linear(sc->fifo.fp[USB_FIFO_RX], buf,
	    UEP_PACKET_LEN_REPORT, 1);
}