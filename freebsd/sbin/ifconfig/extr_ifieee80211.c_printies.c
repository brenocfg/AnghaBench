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
typedef  int u_int8_t ;

/* Variables and functions */
#define  IEEE80211_ELEMID_APCHANREP 144 
#define  IEEE80211_ELEMID_BSSLOAD 143 
#define  IEEE80211_ELEMID_COUNTRY 142 
#define  IEEE80211_ELEMID_DSPARMS 141 
#define  IEEE80211_ELEMID_ERP 140 
#define  IEEE80211_ELEMID_HTCAP 139 
#define  IEEE80211_ELEMID_HTINFO 138 
#define  IEEE80211_ELEMID_MESHCONF 137 
#define  IEEE80211_ELEMID_MESHID 136 
#define  IEEE80211_ELEMID_RATES 135 
#define  IEEE80211_ELEMID_RSN 134 
#define  IEEE80211_ELEMID_SSID 133 
#define  IEEE80211_ELEMID_VENDOR 132 
#define  IEEE80211_ELEMID_VHT_CAP 131 
#define  IEEE80211_ELEMID_VHT_OPMODE 130 
#define  IEEE80211_ELEMID_VHT_PWR_ENV 129 
#define  IEEE80211_ELEMID_XRATES 128 
 char* iename (int const) ; 
 int /*<<< orphan*/  isatherosoui (int const*) ; 
 int /*<<< orphan*/  istdmaoui (int const*) ; 
 int /*<<< orphan*/  iswmeinfo (int const*) ; 
 int /*<<< orphan*/  iswmeparam (int const*) ; 
 int /*<<< orphan*/  iswpaoui (int const*) ; 
 int /*<<< orphan*/  iswpsoui (int const*) ; 
 int /*<<< orphan*/  printapchanrep (char*,int const*,int,int) ; 
 int /*<<< orphan*/  printathie (char*,int const*,int,int) ; 
 int /*<<< orphan*/  printbssload (char*,int const*,int,int) ; 
 int /*<<< orphan*/  printcountry (char*,int const*,int,int) ; 
 int /*<<< orphan*/  printf (char*,int const) ; 
 int /*<<< orphan*/  printhtcap (char*,int const*,int,int) ; 
 int /*<<< orphan*/  printhtinfo (char*,int const*,int,int) ; 
 int /*<<< orphan*/  printie (char*,int const*,int,int) ; 
 int /*<<< orphan*/  printmeshconf (char*,int const*,int,int) ; 
 int /*<<< orphan*/  printrates (char*,int const*,int,int) ; 
 int /*<<< orphan*/  printrsnie (char*,int const*,int,int) ; 
 int /*<<< orphan*/  printssid (char*,int const*,int,int) ; 
 int /*<<< orphan*/  printtdmaie (char*,int const*,int,int) ; 
 int /*<<< orphan*/  printvhtcap (char*,int const*,int,int) ; 
 int /*<<< orphan*/  printvhtinfo (char*,int const*,int,int) ; 
 int /*<<< orphan*/  printvhtpwrenv (char*,int const*,int,int) ; 
 int /*<<< orphan*/  printwmeinfo (char*,int const*,int,int) ; 
 int /*<<< orphan*/  printwmeparam (char*,int const*,int,int) ; 
 int /*<<< orphan*/  printwpaie (char*,int const*,int,int) ; 
 int /*<<< orphan*/  printwpsie (char*,int const*,int,int) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static void
printies(const u_int8_t *vp, int ielen, int maxcols)
{
	while (ielen > 0) {
		switch (vp[0]) {
		case IEEE80211_ELEMID_SSID:
			if (verbose)
				printssid(" SSID", vp, 2+vp[1], maxcols);
			break;
		case IEEE80211_ELEMID_RATES:
		case IEEE80211_ELEMID_XRATES:
			if (verbose)
				printrates(vp[0] == IEEE80211_ELEMID_RATES ?
				    " RATES" : " XRATES", vp, 2+vp[1], maxcols);
			break;
		case IEEE80211_ELEMID_DSPARMS:
			if (verbose)
				printf(" DSPARMS<%u>", vp[2]);
			break;
		case IEEE80211_ELEMID_COUNTRY:
			if (verbose)
				printcountry(" COUNTRY", vp, 2+vp[1], maxcols);
			break;
		case IEEE80211_ELEMID_ERP:
			if (verbose)
				printf(" ERP<0x%x>", vp[2]);
			break;
		case IEEE80211_ELEMID_VENDOR:
			if (iswpaoui(vp))
				printwpaie(" WPA", vp, 2+vp[1], maxcols);
			else if (iswmeinfo(vp))
				printwmeinfo(" WME", vp, 2+vp[1], maxcols);
			else if (iswmeparam(vp))
				printwmeparam(" WME", vp, 2+vp[1], maxcols);
			else if (isatherosoui(vp))
				printathie(" ATH", vp, 2+vp[1], maxcols);
			else if (iswpsoui(vp))
				printwpsie(" WPS", vp, 2+vp[1], maxcols);
			else if (istdmaoui(vp))
				printtdmaie(" TDMA", vp, 2+vp[1], maxcols);
			else if (verbose)
				printie(" VEN", vp, 2+vp[1], maxcols);
			break;
		case IEEE80211_ELEMID_RSN:
			printrsnie(" RSN", vp, 2+vp[1], maxcols);
			break;
		case IEEE80211_ELEMID_HTCAP:
			printhtcap(" HTCAP", vp, 2+vp[1], maxcols);
			break;
		case IEEE80211_ELEMID_HTINFO:
			if (verbose)
				printhtinfo(" HTINFO", vp, 2+vp[1], maxcols);
			break;
		case IEEE80211_ELEMID_MESHID:
			if (verbose)
				printssid(" MESHID", vp, 2+vp[1], maxcols);
			break;
		case IEEE80211_ELEMID_MESHCONF:
			printmeshconf(" MESHCONF", vp, 2+vp[1], maxcols);
			break;
		case IEEE80211_ELEMID_VHT_CAP:
			printvhtcap(" VHTCAP", vp, 2+vp[1], maxcols);
			break;
		case IEEE80211_ELEMID_VHT_OPMODE:
			printvhtinfo(" VHTOPMODE", vp, 2+vp[1], maxcols);
			break;
		case IEEE80211_ELEMID_VHT_PWR_ENV:
			printvhtpwrenv(" VHTPWRENV", vp, 2+vp[1], maxcols);
			break;
		case IEEE80211_ELEMID_BSSLOAD:
			printbssload(" BSSLOAD", vp, 2+vp[1], maxcols);
			break;
		case IEEE80211_ELEMID_APCHANREP:
			printapchanrep(" APCHANREP", vp, 2+vp[1], maxcols);
			break;
		default:
			if (verbose)
				printie(iename(vp[0]), vp, 2+vp[1], maxcols);
			break;
		}
		ielen -= 2+vp[1];
		vp += 2+vp[1];
	}
}