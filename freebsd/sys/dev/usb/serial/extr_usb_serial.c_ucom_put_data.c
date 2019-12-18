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
typedef  unsigned int uint32_t ;
typedef  size_t uint16_t ;
struct usb_page_search {unsigned int length; char* buffer; } ;
struct usb_page_cache {int dummy; } ;
struct ucom_softc {int sc_flag; scalar_t__ sc_jitterbuf_in; scalar_t__ sc_jitterbuf_out; char* sc_jitterbuf; struct tty* sc_tty; } ;
struct tty {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,struct tty*,...) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int UCOM_CONS_BUFSIZE ; 
 int UCOM_FLAG_CONSOLE ; 
 int UCOM_FLAG_RTS_IFLOW ; 
 size_t UCOM_JITTERBUF_SIZE ; 
 int /*<<< orphan*/  UCOM_MTX_ASSERT (struct ucom_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ tty_gone (struct tty*) ; 
 scalar_t__ ttydisc_can_bypass (struct tty*) ; 
 int ttydisc_rint (struct tty*,char,int /*<<< orphan*/ ) ; 
 unsigned int ttydisc_rint_bypass (struct tty*,char*,unsigned int) ; 
 int /*<<< orphan*/  ttydisc_rint_done (struct tty*) ; 
 scalar_t__ ucom_cons_rx_buf ; 
 int ucom_cons_rx_high ; 
 int ucom_cons_rx_low ; 
 int /*<<< orphan*/  ucom_rts (struct ucom_softc*,int) ; 
 int /*<<< orphan*/  usbd_copy_out (struct usb_page_cache*,unsigned int,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  usbd_get_page (struct usb_page_cache*,unsigned int,struct usb_page_search*) ; 

void
ucom_put_data(struct ucom_softc *sc, struct usb_page_cache *pc,
    uint32_t offset, uint32_t len)
{
	struct usb_page_search res;
	struct tty *tp = sc->sc_tty;
	char *buf;
	uint32_t cnt;

	UCOM_MTX_ASSERT(sc, MA_OWNED);

	if (sc->sc_flag & UCOM_FLAG_CONSOLE) {
		unsigned int temp;

		/* get maximum RX length */

		temp = (UCOM_CONS_BUFSIZE - 1) - ucom_cons_rx_high + ucom_cons_rx_low;
		temp %= UCOM_CONS_BUFSIZE;

		/* limit RX length */

		if (temp > (UCOM_CONS_BUFSIZE - ucom_cons_rx_high))
			temp = (UCOM_CONS_BUFSIZE - ucom_cons_rx_high);

		if (temp > len)
			temp = len;

		/* copy out data */

		usbd_copy_out(pc, offset, ucom_cons_rx_buf + ucom_cons_rx_high, temp);

		/* update counters */

		ucom_cons_rx_high += temp;
		ucom_cons_rx_high %= UCOM_CONS_BUFSIZE;

		return;
	}

	if (tty_gone(tp))
		return;			/* multiport device polling */

	if (len == 0)
		return;			/* no data */

	/* set a flag to prevent recursation ? */

	while (len > 0) {

		usbd_get_page(pc, offset, &res);

		if (res.length > len) {
			res.length = len;
		}
		len -= res.length;
		offset += res.length;

		/* pass characters to tty layer */

		buf = res.buffer;
		cnt = res.length;

		/* first check if we can pass the buffer directly */

		if (ttydisc_can_bypass(tp)) {

			/* clear any jitter buffer */
			sc->sc_jitterbuf_in = 0;
			sc->sc_jitterbuf_out = 0;

			if (ttydisc_rint_bypass(tp, buf, cnt) != cnt) {
				DPRINTF("tp=%p, data lost\n", tp);
			}
			continue;
		}
		/* need to loop */

		for (cnt = 0; cnt != res.length; cnt++) {
			if (sc->sc_jitterbuf_in != sc->sc_jitterbuf_out ||
			    ttydisc_rint(tp, buf[cnt], 0) == -1) {
				uint16_t end;
				uint16_t pos;

				pos = sc->sc_jitterbuf_in;
				end = sc->sc_jitterbuf_out +
				    UCOM_JITTERBUF_SIZE - 1;
				if (end >= UCOM_JITTERBUF_SIZE)
					end -= UCOM_JITTERBUF_SIZE;

				for (; cnt != res.length; cnt++) {
					if (pos == end)
						break;
					sc->sc_jitterbuf[pos] = buf[cnt];
					pos++;
					if (pos >= UCOM_JITTERBUF_SIZE)
						pos -= UCOM_JITTERBUF_SIZE;
				}

				sc->sc_jitterbuf_in = pos;

				/* set RTS in async fashion */
				if (sc->sc_flag & UCOM_FLAG_RTS_IFLOW)
					ucom_rts(sc, 1);

				DPRINTF("tp=%p, lost %d "
				    "chars\n", tp, res.length - cnt);
				break;
			}
		}
	}
	ttydisc_rint_done(tp);
}