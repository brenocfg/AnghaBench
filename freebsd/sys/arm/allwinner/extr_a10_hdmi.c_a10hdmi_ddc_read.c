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
typedef  int /*<<< orphan*/  uint8_t ;
struct a10hdmi_softc {int /*<<< orphan*/  res; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDC_ADDR ; 
 int /*<<< orphan*/  DDC_BLKLEN ; 
 int /*<<< orphan*/  DDC_FIFO ; 
 int EDID_LENGTH ; 
 int a10hdmi_ddc_xfer (struct a10hdmi_softc*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  bus_read_multi_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int min (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
a10hdmi_ddc_read(struct a10hdmi_softc *sc, int block, uint8_t *edid)
{
	int resid, off, len, error;
	uint8_t *pbuf;

	pbuf = edid;
	resid = EDID_LENGTH;
	off = (block & 1) ? EDID_LENGTH : 0;

	while (resid > 0) {
		len = min(resid, DDC_BLKLEN);
		error = a10hdmi_ddc_xfer(sc, DDC_ADDR, block >> 1, off, len);
		if (error != 0)
			return (error);

		bus_read_multi_1(sc->res, DDC_FIFO, pbuf, len);

		pbuf += len;
		off += len;
		resid -= len;
	}

	return (0);
}