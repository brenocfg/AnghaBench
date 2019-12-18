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
typedef  int /*<<< orphan*/  uint32_t ;
struct upgt_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_mtx; scalar_t__ sc_memaddr_frame_start; } ;
struct upgt_lmac_mem {int /*<<< orphan*/  chksum; void* addr; } ;
struct upgt_lmac_header {int dummy; } ;
struct TYPE_4__ {scalar_t__ flags; void* type; void* reqid; } ;
struct TYPE_3__ {void* len; int /*<<< orphan*/  type; scalar_t__ flags; } ;
struct upgt_lmac_eeprom {void* len; void* offset; TYPE_2__ header2; TYPE_1__ header1; } ;
struct upgt_data {int buflen; scalar_t__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (struct upgt_softc*,int /*<<< orphan*/ ,char*,int,int) ; 
 int EIO ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  MCLBYTES ; 
 int /*<<< orphan*/  UPGT_DEBUG_FW ; 
 int UPGT_EEPROM_BLOCK_SIZE ; 
 int UPGT_EEPROM_SIZE ; 
 int /*<<< orphan*/  UPGT_H1_TYPE_CTRL ; 
 int UPGT_H2_TYPE_EEPROM ; 
 int /*<<< orphan*/  UPGT_LOCK (struct upgt_softc*) ; 
 scalar_t__ UPGT_MEMSIZE_FRAME_HEAD ; 
 int /*<<< orphan*/  UPGT_UNLOCK (struct upgt_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 void* htole16 (int) ; 
 void* htole32 (scalar_t__) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mtx_sleep (struct upgt_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upgt_bulk_tx (struct upgt_softc*,struct upgt_data*) ; 
 int /*<<< orphan*/  upgt_chksum_le (int /*<<< orphan*/ *,int) ; 
 struct upgt_data* upgt_getbuf (struct upgt_softc*) ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
upgt_eeprom_read(struct upgt_softc *sc)
{
	struct upgt_data *data_cmd;
	struct upgt_lmac_mem *mem;
	struct upgt_lmac_eeprom	*eeprom;
	int block, error, offset;

	UPGT_LOCK(sc);
	usb_pause_mtx(&sc->sc_mtx, 100);

	offset = 0;
	block = UPGT_EEPROM_BLOCK_SIZE;
	while (offset < UPGT_EEPROM_SIZE) {
		DPRINTF(sc, UPGT_DEBUG_FW,
		    "request EEPROM block (offset=%d, len=%d)\n", offset, block);

		data_cmd = upgt_getbuf(sc);
		if (data_cmd == NULL) {
			UPGT_UNLOCK(sc);
			return (ENOBUFS);
		}

		/*
		 * Transmit the URB containing the CMD data.
		 */
		memset(data_cmd->buf, 0, MCLBYTES);

		mem = (struct upgt_lmac_mem *)data_cmd->buf;
		mem->addr = htole32(sc->sc_memaddr_frame_start +
		    UPGT_MEMSIZE_FRAME_HEAD);

		eeprom = (struct upgt_lmac_eeprom *)(mem + 1);
		eeprom->header1.flags = 0;
		eeprom->header1.type = UPGT_H1_TYPE_CTRL;
		eeprom->header1.len = htole16((
		    sizeof(struct upgt_lmac_eeprom) -
		    sizeof(struct upgt_lmac_header)) + block);

		eeprom->header2.reqid = htole32(sc->sc_memaddr_frame_start);
		eeprom->header2.type = htole16(UPGT_H2_TYPE_EEPROM);
		eeprom->header2.flags = 0;

		eeprom->offset = htole16(offset);
		eeprom->len = htole16(block);

		data_cmd->buflen = sizeof(*mem) + sizeof(*eeprom) + block;

		mem->chksum = upgt_chksum_le((uint32_t *)eeprom,
		    data_cmd->buflen - sizeof(*mem));
		upgt_bulk_tx(sc, data_cmd);

		error = mtx_sleep(sc, &sc->sc_mtx, 0, "eeprom_request", hz);
		if (error != 0) {
			device_printf(sc->sc_dev,
			    "timeout while waiting for EEPROM data\n");
			UPGT_UNLOCK(sc);
			return (EIO);
		}

		offset += block;
		if (UPGT_EEPROM_SIZE - offset < block)
			block = UPGT_EEPROM_SIZE - offset;
	}

	UPGT_UNLOCK(sc);
	return (0);
}