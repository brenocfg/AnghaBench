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
struct ahd_softc {int bugs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_ASSERT_MODES (struct ahd_softc*,int,int) ; 
 int AHD_CLRLQO_AUTOCLR_BUG ; 
 int AHD_MODE_CFG_MSK ; 
 int AHD_MODE_UNKNOWN_MSK ; 
 int CLRATNO ; 
 int CLRBUSFREE ; 
 int /*<<< orphan*/  CLRINT ; 
 int CLRIOERR ; 
 int CLRLIQABORT ; 
 int CLRLQIATNCMD ; 
 int CLRLQIATNLQ ; 
 int CLRLQIATNQAS ; 
 int CLRLQIBADLQI ; 
 int CLRLQIBADLQT ; 
 int CLRLQICRCI_LQ ; 
 int CLRLQICRCI_NLQ ; 
 int CLRLQICRCT1 ; 
 int CLRLQICRCT2 ; 
 int /*<<< orphan*/  CLRLQIINT0 ; 
 int /*<<< orphan*/  CLRLQIINT1 ; 
 int CLRLQIOVERI_LQ ; 
 int CLRLQIOVERI_NLQ ; 
 int CLRLQIPHASE_LQ ; 
 int CLRLQIPHASE_NLQ ; 
 int CLRLQOATNLQ ; 
 int CLRLQOATNPKT ; 
 int CLRLQOBADQAS ; 
 int CLRLQOBUSFREE ; 
 int CLRLQOINITSCBPERR ; 
 int /*<<< orphan*/  CLRLQOINT0 ; 
 int /*<<< orphan*/  CLRLQOINT1 ; 
 int CLRLQOPHACHGINPKT ; 
 int CLRLQOSTOPI2 ; 
 int CLRLQOSTOPT2 ; 
 int CLRLQOTARGSCBPERR ; 
 int CLRLQOTCRC ; 
 int CLRNONPACKREQ ; 
 int CLRNTRAMPERR ; 
 int CLROSRAMPERR ; 
 int CLROVERRUN ; 
 int CLRREQINIT ; 
 int CLRSCSIINT ; 
 int CLRSCSIPERR ; 
 int CLRSCSIRSTI ; 
 int CLRSELDI ; 
 int CLRSELDO ; 
 int CLRSELINGO ; 
 int CLRSELTIMEO ; 
 int /*<<< orphan*/  CLRSINT0 ; 
 int /*<<< orphan*/  CLRSINT1 ; 
 int /*<<< orphan*/  CLRSINT3 ; 
 int /*<<< orphan*/  ahd_outb (struct ahd_softc*,int /*<<< orphan*/ ,int) ; 

void
ahd_clear_intstat(struct ahd_softc *ahd)
{
	AHD_ASSERT_MODES(ahd, ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK),
			 ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK));
	/* Clear any interrupt conditions this may have caused */
	ahd_outb(ahd, CLRLQIINT0, CLRLQIATNQAS|CLRLQICRCT1|CLRLQICRCT2
				 |CLRLQIBADLQT|CLRLQIATNLQ|CLRLQIATNCMD);
	ahd_outb(ahd, CLRLQIINT1, CLRLQIPHASE_LQ|CLRLQIPHASE_NLQ|CLRLIQABORT
				 |CLRLQICRCI_LQ|CLRLQICRCI_NLQ|CLRLQIBADLQI
				 |CLRLQIOVERI_LQ|CLRLQIOVERI_NLQ|CLRNONPACKREQ);
	ahd_outb(ahd, CLRLQOINT0, CLRLQOTARGSCBPERR|CLRLQOSTOPT2|CLRLQOATNLQ
				 |CLRLQOATNPKT|CLRLQOTCRC);
	ahd_outb(ahd, CLRLQOINT1, CLRLQOINITSCBPERR|CLRLQOSTOPI2|CLRLQOBADQAS
				 |CLRLQOBUSFREE|CLRLQOPHACHGINPKT);
	if ((ahd->bugs & AHD_CLRLQO_AUTOCLR_BUG) != 0) {
		ahd_outb(ahd, CLRLQOINT0, 0);
		ahd_outb(ahd, CLRLQOINT1, 0);
	}
	ahd_outb(ahd, CLRSINT3, CLRNTRAMPERR|CLROSRAMPERR);
	ahd_outb(ahd, CLRSINT1, CLRSELTIMEO|CLRATNO|CLRSCSIRSTI
				|CLRBUSFREE|CLRSCSIPERR|CLRREQINIT);
	ahd_outb(ahd, CLRSINT0, CLRSELDO|CLRSELDI|CLRSELINGO
			        |CLRIOERR|CLROVERRUN);
	ahd_outb(ahd, CLRINT, CLRSCSIINT);
}