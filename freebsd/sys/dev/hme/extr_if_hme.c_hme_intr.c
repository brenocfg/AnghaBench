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
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct hme_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HME_LOCK (struct hme_softc*) ; 
 int /*<<< orphan*/  HME_SEBI_STAT ; 
 int HME_SEB_READ_4 (struct hme_softc*,int /*<<< orphan*/ ) ; 
 int HME_SEB_STAT_ALL_ERRORS ; 
 int HME_SEB_STAT_HOSTTOTX ; 
 int HME_SEB_STAT_RXTOHOST ; 
 int HME_SEB_STAT_TXALL ; 
 int /*<<< orphan*/  HME_UNLOCK (struct hme_softc*) ; 
 int /*<<< orphan*/  KTR_HME ; 
 int /*<<< orphan*/  hme_eint (struct hme_softc*,int) ; 
 int /*<<< orphan*/  hme_rint (struct hme_softc*) ; 
 int /*<<< orphan*/  hme_tint (struct hme_softc*) ; 

void
hme_intr(void *v)
{
	struct hme_softc *sc = (struct hme_softc *)v;
	u_int32_t status;

	HME_LOCK(sc);
	status = HME_SEB_READ_4(sc, HME_SEBI_STAT);
	CTR1(KTR_HME, "hme_intr: status %#x", (u_int)status);

	if ((status & HME_SEB_STAT_ALL_ERRORS) != 0)
		hme_eint(sc, status);

	if ((status & HME_SEB_STAT_RXTOHOST) != 0)
		hme_rint(sc);

	if ((status & (HME_SEB_STAT_TXALL | HME_SEB_STAT_HOSTTOTX)) != 0)
		hme_tint(sc);
	HME_UNLOCK(sc);
}