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
typedef  int /*<<< orphan*/  vap ;
struct ifnet {int /*<<< orphan*/  iv_debug; struct ifnet* iv_ifp; struct ifnet* iv_ic; int /*<<< orphan*/  if_xname; } ;
struct ieee80211vap {int /*<<< orphan*/  iv_debug; struct ieee80211vap* iv_ifp; struct ieee80211vap* iv_ic; int /*<<< orphan*/  if_xname; } ;
struct ieee80211com {int /*<<< orphan*/  iv_debug; struct ieee80211com* iv_ifp; struct ieee80211com* iv_ic; int /*<<< orphan*/  if_xname; } ;
typedef  int /*<<< orphan*/  ifp ;
typedef  int /*<<< orphan*/  ic ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_MSG_CRYPTO ; 
 int /*<<< orphan*/ * ccmptests ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  ieee80211_crypto_attach (struct ifnet*) ; 
 int /*<<< orphan*/  ieee80211_crypto_detach (struct ifnet*) ; 
 int /*<<< orphan*/  ieee80211_crypto_vattach (struct ifnet*) ; 
 int /*<<< orphan*/  ieee80211_crypto_vdetach (struct ifnet*) ; 
 int /*<<< orphan*/  memset (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int nitems (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 scalar_t__ runtest (struct ifnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 
 int tests ; 

__attribute__((used)) static int
init_crypto_ccmp_test(void)
{
	struct ieee80211com ic;
	struct ieee80211vap vap;
	struct ifnet ifp;
	int i, pass, total;

	memset(&ic, 0, sizeof(ic));
	memset(&vap, 0, sizeof(vap));
	memset(&ifp, 0, sizeof(ifp));

	ieee80211_crypto_attach(&ic);

	/* some minimal initialization */
	strncpy(ifp.if_xname, "test_ccmp", sizeof(ifp.if_xname));
	vap.iv_ic = &ic;
	vap.iv_ifp = &ifp;
	if (debug)
		vap.iv_debug = IEEE80211_MSG_CRYPTO;
	ieee80211_crypto_vattach(&vap);

	pass = 0;
	total = 0;
	for (i = 0; i < nitems(ccmptests); i++)
		if (tests & (1<<i)) {
			total++;
			pass += runtest(&vap, &ccmptests[i]);
		}
	printf("%u of %u 802.11i AES-CCMP test vectors passed\n", pass, total);

	ieee80211_crypto_vdetach(&vap);
	ieee80211_crypto_detach(&ic);

	return (pass == total ? 0 : -1);
}