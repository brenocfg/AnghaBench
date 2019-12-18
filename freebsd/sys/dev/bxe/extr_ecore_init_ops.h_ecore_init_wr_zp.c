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
typedef  int uint32_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ ECORE_CPU_TO_LE32 (int) ; 
 scalar_t__ GUNZIP_BUF (struct bxe_softc*) ; 
 int GUNZIP_OUTLEN (struct bxe_softc*) ; 
 int ecore_gunzip (struct bxe_softc*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * ecore_sel_blob (struct bxe_softc*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ecore_write_big_buf_wb (struct bxe_softc*,int,int) ; 

__attribute__((used)) static void ecore_init_wr_zp(struct bxe_softc *sc, uint32_t addr, uint32_t len,
			     uint32_t blob_off)
{
	const uint8_t *data = NULL;
	int rc;
	uint32_t i;

	data = ecore_sel_blob(sc, addr, data) + blob_off*4;

	rc = ecore_gunzip(sc, data, len);
	if (rc)
		return;

	/* gunzip_outlen is in dwords */
	len = GUNZIP_OUTLEN(sc);
	for (i = 0; i < len; i++)
		((uint32_t *)GUNZIP_BUF(sc))[i] = (uint32_t)
				ECORE_CPU_TO_LE32(((uint32_t *)GUNZIP_BUF(sc))[i]);

	ecore_write_big_buf_wb(sc, addr, len);
}