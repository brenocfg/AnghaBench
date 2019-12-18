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
typedef  int u_int ;
struct cfi_softc {int sc_width; } ;

/* Variables and functions */
 int CFI_QRY_CMD_ADDR ; 
 int /*<<< orphan*/  CFI_QRY_CMD_DATA ; 
 int /*<<< orphan*/  cfi_read (struct cfi_softc*,int) ; 
 int /*<<< orphan*/  cfi_reset_default (struct cfi_softc*) ; 
 int /*<<< orphan*/  cfi_write (struct cfi_softc*,int,int /*<<< orphan*/ ) ; 

uint8_t
cfi_read_qry(struct cfi_softc *sc, u_int ofs)
{
	uint8_t val;
 
	cfi_write(sc, CFI_QRY_CMD_ADDR * sc->sc_width, CFI_QRY_CMD_DATA); 
	val = cfi_read(sc, ofs * sc->sc_width);
	cfi_reset_default(sc);
	return (val);
}