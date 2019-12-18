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
typedef  int uint8_t ;
struct umoscom_softc {int dummy; } ;
struct ucom_softc {struct umoscom_softc* sc_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int SER_CTS ; 
 int SER_DCD ; 
 int SER_DSR ; 
 int SER_RI ; 
 int /*<<< orphan*/  UMOSCOM_LSR ; 
 int /*<<< orphan*/  UMOSCOM_MSR ; 
 int UMOSCOM_MSR_CD ; 
 int UMOSCOM_MSR_CTS ; 
 int UMOSCOM_MSR_RI ; 
 int UMOSCOM_MSR_RTS ; 
 int umoscom_cfg_read (struct umoscom_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
umoscom_cfg_get_status(struct ucom_softc *ucom, uint8_t *p_lsr, uint8_t *p_msr)
{
	struct umoscom_softc *sc = ucom->sc_parent;
	uint8_t msr;

	DPRINTFN(5, "\n");

	/*
	 * Read status registers.  MSR bits need translation from ns16550 to
	 * SER_* values.  LSR bits are ns16550 in hardware and ucom.
	 */

	*p_lsr = umoscom_cfg_read(sc, UMOSCOM_LSR);
	msr = umoscom_cfg_read(sc, UMOSCOM_MSR);

	/* translate bits */

	if (msr & UMOSCOM_MSR_CTS)
		*p_msr |= SER_CTS;

	if (msr & UMOSCOM_MSR_CD)
		*p_msr |= SER_DCD;

	if (msr & UMOSCOM_MSR_RI)
		*p_msr |= SER_RI;

	if (msr & UMOSCOM_MSR_RTS)
		*p_msr |= SER_DSR;
}