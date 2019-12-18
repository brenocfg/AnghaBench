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
typedef  int uint64_t ;
typedef  int uint16_t ;
struct uart_opal_softc {scalar_t__ protocol; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  vtermid; int /*<<< orphan*/  outseqno; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPAL_CONSOLE_WRITE ; 
 scalar_t__ OPAL_RAW ; 
 int OPAL_SUCCESS ; 
 char VS_DATA_PACKET_HEADER ; 
 int /*<<< orphan*/  memcpy (char*,void*,size_t) ; 
 int opal_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_opal_real_map_outbuffer (int*,int*) ; 
 int /*<<< orphan*/  uart_opal_real_unmap_outbuffer (int*) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
uart_opal_put(struct uart_opal_softc *sc, void *buffer, size_t bufsize)
{
	uint16_t seqno;
	uint64_t len;
	char	cbuf[16];
	int	err;
	uint64_t olen = (uint64_t)&len;
	uint64_t obuf = (uint64_t)cbuf;

	if (sc->protocol == OPAL_RAW) {
		obuf = (uint64_t)buffer;
		len = bufsize;

		uart_opal_real_map_outbuffer(&obuf, &olen);
		err = opal_call(OPAL_CONSOLE_WRITE, sc->vtermid, olen, obuf);
		uart_opal_real_unmap_outbuffer(&len);
	} else {
		uart_lock(&sc->sc_mtx);
		if (bufsize > 12)
			bufsize = 12;
		seqno = sc->outseqno++;
		cbuf[0] = VS_DATA_PACKET_HEADER;
		cbuf[1] = 4 + bufsize; /* total length */
		cbuf[2] = (seqno >> 8) & 0xff;
		cbuf[3] = seqno & 0xff;
		memcpy(&cbuf[4], buffer, bufsize);
		len = 4 + bufsize;

		uart_opal_real_map_outbuffer(&obuf, &olen);
		err = opal_call(OPAL_CONSOLE_WRITE, sc->vtermid, olen, obuf);
		uart_opal_real_unmap_outbuffer(&len);

		uart_unlock(&sc->sc_mtx);

		len -= 4;
	}

#if 0
	if (err != OPAL_SUCCESS)
		len = 0;
#endif

	return (len);
}