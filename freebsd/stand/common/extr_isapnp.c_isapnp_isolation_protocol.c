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
struct pnpinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CONTROL ; 
 int /*<<< orphan*/  SERIAL_ISOLATION ; 
 int /*<<< orphan*/  SET_CSN ; 
 int /*<<< orphan*/  SET_RD_DATA ; 
 int /*<<< orphan*/  WAKE ; 
 int /*<<< orphan*/  _PNP_ADDRESS ; 
 int _PNP_ID_LEN ; 
 int /*<<< orphan*/  delay (int) ; 
 scalar_t__ isapnp_get_serial (int /*<<< orphan*/ *) ; 
 int isapnp_readport ; 
 scalar_t__ isapnp_scan_resdata (struct pnpinfo*) ; 
 int /*<<< orphan*/  isapnp_send_Initiation_LFSR () ; 
 int /*<<< orphan*/  isapnp_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnp_addident (struct pnpinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnp_addinfo (struct pnpinfo*) ; 
 struct pnpinfo* pnp_allocinfo () ; 
 int /*<<< orphan*/  pnp_eisaformat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pnp_freeinfo (struct pnpinfo*) ; 

__attribute__((used)) static int
isapnp_isolation_protocol(void)
{
    int			csn;
    struct pnpinfo	*pi;
    uint8_t		cardid[_PNP_ID_LEN];
    int			ndevs;

    isapnp_send_Initiation_LFSR();
    ndevs = 0;
    
    isapnp_write(CONFIG_CONTROL, 0x04);	/* Reset CSN for All Cards */

    for (csn = 1; ; csn++) {
	/* Wake up cards without a CSN (ie. all of them) */
	isapnp_write(WAKE, 0);
	isapnp_write(SET_RD_DATA, (isapnp_readport >> 2));
	outb(_PNP_ADDRESS, SERIAL_ISOLATION);
	delay(1000);	/* Delay 1 msec */

	if (isapnp_get_serial(cardid)) {
	    isapnp_write(SET_CSN, csn);
	    pi = pnp_allocinfo();
	    ndevs++;
	    pnp_addident(pi, pnp_eisaformat(cardid));
	    /* scan the card obtaining all the identifiers it holds */
	    if (isapnp_scan_resdata(pi)) {
		pnp_freeinfo(pi);	/* error getting data, ignore */
	    } else {
		pnp_addinfo(pi);
	    }
	} else {
	    break;
	}
    }
    /* Move all cards to wait-for-key state */
    while (--csn > 0) {
	isapnp_send_Initiation_LFSR();
	isapnp_write(WAKE, csn);
	isapnp_write(CONFIG_CONTROL, 0x02);
	delay(1000); /* XXX is it really necessary ? */
	csn--;
    }
    return(ndevs);
}