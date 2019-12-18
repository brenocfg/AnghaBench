#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ic_nchans; } ;
struct ieee80211_devcaps_req {scalar_t__ dc_drivercaps; scalar_t__ dc_cryptocaps; scalar_t__ dc_htcaps; scalar_t__ dc_vhtcaps; TYPE_1__ dc_chaninfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CRYPTO_BITS ; 
 int /*<<< orphan*/  IEEE80211_C_BITS ; 
 int /*<<< orphan*/  IEEE80211_DEVCAPS_SIZE (int) ; 
 int /*<<< orphan*/  IEEE80211_HTCAP_BITS ; 
 int /*<<< orphan*/  IEEE80211_VHTCAP_BITS ; 
 int MAXCHAN ; 
 TYPE_1__* chaninfo ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (struct ieee80211_devcaps_req*) ; 
 int /*<<< orphan*/  getdevcaps (int,struct ieee80211_devcaps_req*) ; 
 struct ieee80211_devcaps_req* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_channels (int,TYPE_1__*,int,scalar_t__) ; 
 int /*<<< orphan*/  printb (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putchar (char) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void
list_capabilities(int s)
{
	struct ieee80211_devcaps_req *dc;

	if (verbose)
		dc = malloc(IEEE80211_DEVCAPS_SIZE(MAXCHAN));
	else
		dc = malloc(IEEE80211_DEVCAPS_SIZE(1));
	if (dc == NULL)
		errx(1, "no space for device capabilities");
	dc->dc_chaninfo.ic_nchans = verbose ? MAXCHAN : 1;
	getdevcaps(s, dc);
	printb("drivercaps", dc->dc_drivercaps, IEEE80211_C_BITS);
	if (dc->dc_cryptocaps != 0 || verbose) {
		putchar('\n');
		printb("cryptocaps", dc->dc_cryptocaps, IEEE80211_CRYPTO_BITS);
	}
	if (dc->dc_htcaps != 0 || verbose) {
		putchar('\n');
		printb("htcaps", dc->dc_htcaps, IEEE80211_HTCAP_BITS);
	}
	if (dc->dc_vhtcaps != 0 || verbose) {
		putchar('\n');
		printb("vhtcaps", dc->dc_vhtcaps, IEEE80211_VHTCAP_BITS);
	}

	putchar('\n');
	if (verbose) {
		chaninfo = &dc->dc_chaninfo;	/* XXX */
		print_channels(s, &dc->dc_chaninfo, 1/*allchans*/, verbose);
	}
	free(dc);
}