#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int16_t ;
struct ieee80211_channel {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  ah_getCapability; } ;
struct TYPE_5__ {int halLow5GhzChan; int halHigh5GhzChan; int halLow2GhzChan; int halHigh2GhzChan; void* halChanQuarterRate; void* halChanHalfRate; int /*<<< orphan*/  halWirelessModes; } ;
struct ath_hal_private {int ah_currentRD; TYPE_2__ h; void* ah_opmode; TYPE_1__ ah_caps; int /*<<< orphan*/  ah_getChipPowerLimits; int /*<<< orphan*/  ah_eepromRead; int /*<<< orphan*/  ah_getWirelessModes; int /*<<< orphan*/  ah_getChannelEdges; } ;
typedef  int int16_t ;
typedef  int /*<<< orphan*/  ahp ;
typedef  void* HAL_BOOL ;

/* Variables and functions */
 void* AH_FALSE ; 
 void* AH_TRUE ; 
 scalar_t__ CHECKMODES (int,int) ; 
 scalar_t__ CTRY_DEFAULT ; 
 int /*<<< orphan*/  HAL_DEBUG_ANY ; 
 int HAL_MODE_108G ; 
 int HAL_MODE_11A ; 
 int HAL_MODE_11B ; 
 int HAL_MODE_11G ; 
 int /*<<< orphan*/  HAL_MODE_ALL ; 
 int HAL_MODE_HT ; 
 int HAL_MODE_HT20 ; 
 int HAL_MODE_HT40 ; 
 int HAL_MODE_TURBO ; 
 void* HAL_M_HOSTAP ; 
 void* HAL_M_IBSS ; 
 void* HAL_M_MONITOR ; 
 void* HAL_M_STA ; 
 scalar_t__ HAL_OK ; 
 int /*<<< orphan*/  IEEE80211_CHAN_4MSXMIT ; 
 int /*<<< orphan*/  IEEE80211_CHAN_DFS ; 
 int IEEE80211_CHAN_MAX ; 
#define  MAX_RATE_POWER 128 
 int /*<<< orphan*/  anychan (struct ieee80211_channel*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_hal_debug ; 
 scalar_t__ ath_hal_getchannels (TYPE_2__*,struct ieee80211_channel*,int,int*,int,scalar_t__,int,void*) ; 
 int /*<<< orphan*/  calctxpower (TYPE_2__*,int,struct ieee80211_channel*,int,int,int*) ; 
 scalar_t__ cc ; 
 int /*<<< orphan*/  cclist () ; 
 int /*<<< orphan*/  cclookup (char*,int*,scalar_t__*) ; 
 int dopassive ; 
 int /*<<< orphan*/  dumpchannels (TYPE_2__*,int,struct ieee80211_channel*,int*) ; 
 int /*<<< orphan*/  eepromRead ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  getCapability ; 
 int /*<<< orphan*/  getChannelEdges ; 
 int /*<<< orphan*/  getChipPowerLimits ; 
 int /*<<< orphan*/  getWirelessModes ; 
 char* getccisoname (scalar_t__) ; 
 char* getccname (scalar_t__) ; 
 int getopt (int,char**,char*) ; 
 char* getrdname (int) ; 
 int /*<<< orphan*/  intersect (struct ieee80211_channel*,int*,int*,struct ieee80211_channel*,int*,int) ; 
 int /*<<< orphan*/  is4ms ; 
 int /*<<< orphan*/  isdfs ; 
 int /*<<< orphan*/  memset (struct ath_hal_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int rd ; 
 int /*<<< orphan*/  rdlist () ; 
 int /*<<< orphan*/  rdlookup (char*,int*) ; 
 void* showchannels ; 
 int /*<<< orphan*/  strncasecmp (int /*<<< orphan*/ ,char*,int) ; 
 void* strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (char*) ; 

int
main(int argc, char *argv[])
{
	static const u_int16_t tpcScaleReductionTable[5] =
		{ 0, 3, 6, 9, MAX_RATE_POWER };
	struct ath_hal_private ahp;
	struct ieee80211_channel achans[IEEE80211_CHAN_MAX];
	int16_t atxpow[IEEE80211_CHAN_MAX];
	struct ieee80211_channel bchans[IEEE80211_CHAN_MAX];
	int16_t btxpow[IEEE80211_CHAN_MAX];
	struct ieee80211_channel gchans[IEEE80211_CHAN_MAX];
	int16_t gtxpow[IEEE80211_CHAN_MAX];
	struct ieee80211_channel tchans[IEEE80211_CHAN_MAX];
	int16_t ttxpow[IEEE80211_CHAN_MAX];
	struct ieee80211_channel tgchans[IEEE80211_CHAN_MAX];
	int16_t tgtxpow[IEEE80211_CHAN_MAX];
	struct ieee80211_channel nchans[IEEE80211_CHAN_MAX];
	int16_t ntxpow[IEEE80211_CHAN_MAX];
	int i, na, nb, ng, nt, ntg, nn;
	HAL_BOOL showall = AH_FALSE;
	HAL_BOOL extendedChanMode = AH_TRUE;
	int modes = 0;
	int16_t tpcReduction, powerLimit;
	int showdfs = 0;
	int show4ms = 0;

	memset(&ahp, 0, sizeof(ahp));
	ahp.ah_getChannelEdges = getChannelEdges;
	ahp.ah_getWirelessModes = getWirelessModes;
	ahp.ah_eepromRead = eepromRead;
	ahp.ah_getChipPowerLimits = getChipPowerLimits;
	ahp.ah_caps.halWirelessModes = HAL_MODE_ALL;
	ahp.ah_caps.halLow5GhzChan = 4920;
	ahp.ah_caps.halHigh5GhzChan = 6100;
	ahp.ah_caps.halLow2GhzChan = 2312;
	ahp.ah_caps.halHigh2GhzChan = 2732;
	ahp.ah_caps.halChanHalfRate = AH_TRUE;
	ahp.ah_caps.halChanQuarterRate = AH_TRUE;
	ahp.h.ah_getCapability = getCapability;
	ahp.ah_opmode = HAL_M_STA;

	tpcReduction = tpcScaleReductionTable[0];
	powerLimit =  MAX_RATE_POWER;

	while ((i = getopt(argc, argv, "acdeflm:pr4ABGhHNT")) != -1)
		switch (i) {
		case 'a':
			showall = AH_TRUE;
			break;
		case 'c':
			showchannels = AH_TRUE;
			break;
		case 'd':
			ath_hal_debug = HAL_DEBUG_ANY;
			break;
		case 'e':
			extendedChanMode = AH_FALSE;
			break;
		case 'f':
			showchannels = AH_FALSE;
			break;
		case 'l':
			cclist();
			rdlist();
			exit(0);
		case 'm':
			if (strncasecmp(optarg, "sta", 2) == 0)
				ahp.ah_opmode = HAL_M_STA;
			else if (strncasecmp(optarg, "ibss", 2) == 0)
				ahp.ah_opmode = HAL_M_IBSS;
			else if (strncasecmp(optarg, "adhoc", 2) == 0)
				ahp.ah_opmode = HAL_M_IBSS;
			else if (strncasecmp(optarg, "ap", 2) == 0)
				ahp.ah_opmode = HAL_M_HOSTAP;
			else if (strncasecmp(optarg, "hostap", 2) == 0)
				ahp.ah_opmode = HAL_M_HOSTAP;
			else if (strncasecmp(optarg, "monitor", 2) == 0)
				ahp.ah_opmode = HAL_M_MONITOR;
			else
				usage(argv[0]);
			break;
		case 'p':
			dopassive = 1;
			break;
		case 'A':
			modes |= HAL_MODE_11A;
			break;
		case 'B':
			modes |= HAL_MODE_11B;
			break;
		case 'G':
			modes |= HAL_MODE_11G;
			break;
		case 'h':
			modes |= HAL_MODE_HT20;
			break;
		case 'H':
			modes |= HAL_MODE_HT40;
			break;
		case 'N':
			modes |= HAL_MODE_HT;
			break;
		case 'T':
			modes |= HAL_MODE_TURBO | HAL_MODE_108G;
			break;
		case 'r':
			showdfs = 1;
			break;
		case '4':
			show4ms = 1;
			break;
		default:
			usage(argv[0]);
		}
	switch (argc - optind)  {
	case 0:
		if (!cclookup("US", &rd, &cc)) {
			printf("%s: unknown country code\n", "US");
			exit(-1);
		}
		break;
	case 1:			/* cc/regdomain */
		if (!cclookup(argv[optind], &rd, &cc)) {
			if (!rdlookup(argv[optind], &rd)) {
				const char* rdname;

				rd = strtoul(argv[optind], NULL, 0);
				rdname = getrdname(rd);
				if (rdname == NULL) {
					printf("%s: unknown country/regulatory "
						"domain code\n", argv[optind]);
					exit(-1);
				}
			}
			cc = CTRY_DEFAULT;
		}
		break;
	default:		/* regdomain cc */
		if (!rdlookup(argv[optind], &rd)) {
			const char* rdname;

			rd = strtoul(argv[optind], NULL, 0);
			rdname = getrdname(rd);
			if (rdname == NULL) {
				printf("%s: unknown country/regulatory "
					"domain code\n", argv[optind]);
				exit(-1);
			}
		}
		if (!cclookup(argv[optind+1], &rd, &cc))
			cc = strtoul(argv[optind+1], NULL, 0);
		break;
	}
	if (cc != CTRY_DEFAULT)
		printf("\n%s (%s, 0x%x, %u) %s (0x%x, %u)\n",
			getccname(cc), getccisoname(cc), cc, cc,
			getrdname(rd), rd, rd);
	else
		printf("\n%s (0x%x, %u)\n",
			getrdname(rd), rd, rd);

	if (modes == 0) {
		/* NB: no HAL_MODE_HT */
		modes = HAL_MODE_11A | HAL_MODE_11B |
			HAL_MODE_11G | HAL_MODE_TURBO | HAL_MODE_108G;
	}
	na = nb = ng = nt = ntg = nn = 0;
	if (modes & HAL_MODE_11G) {
		ahp.ah_currentRD = rd;
		if (ath_hal_getchannels(&ahp.h, gchans, IEEE80211_CHAN_MAX, &ng,
		    HAL_MODE_11G, cc, rd, extendedChanMode) == HAL_OK) {
			calctxpower(&ahp.h, ng, gchans, tpcReduction, powerLimit, gtxpow);
			if (showdfs)
				isdfs |= anychan(gchans, ng, IEEE80211_CHAN_DFS);
			if (show4ms)
				is4ms |= anychan(gchans, ng, IEEE80211_CHAN_4MSXMIT);
		}
	}
	if (modes & HAL_MODE_11B) {
		ahp.ah_currentRD = rd;
		if (ath_hal_getchannels(&ahp.h, bchans, IEEE80211_CHAN_MAX, &nb,
		    HAL_MODE_11B, cc, rd, extendedChanMode) == HAL_OK) {
			calctxpower(&ahp.h, nb, bchans, tpcReduction, powerLimit, btxpow);
			if (showdfs)
				isdfs |= anychan(bchans, nb, IEEE80211_CHAN_DFS);
			if (show4ms)
				is4ms |= anychan(bchans, nb, IEEE80211_CHAN_4MSXMIT);
		}
	}
	if (modes & HAL_MODE_11A) {
		ahp.ah_currentRD = rd;
		if (ath_hal_getchannels(&ahp.h, achans, IEEE80211_CHAN_MAX, &na,
		    HAL_MODE_11A, cc, rd, extendedChanMode) == HAL_OK) {
			calctxpower(&ahp.h, na, achans, tpcReduction, powerLimit, atxpow);
			if (showdfs)
				isdfs |= anychan(achans, na, IEEE80211_CHAN_DFS);
			if (show4ms)
				is4ms |= anychan(achans, na, IEEE80211_CHAN_4MSXMIT);
		}
	}
	if (modes & HAL_MODE_TURBO) {
		ahp.ah_currentRD = rd;
		if (ath_hal_getchannels(&ahp.h, tchans, IEEE80211_CHAN_MAX, &nt,
		    HAL_MODE_TURBO, cc, rd, extendedChanMode) == HAL_OK) {
			calctxpower(&ahp.h, nt, tchans, tpcReduction, powerLimit, ttxpow);
			if (showdfs)
				isdfs |= anychan(tchans, nt, IEEE80211_CHAN_DFS);
			if (show4ms)
				is4ms |= anychan(tchans, nt, IEEE80211_CHAN_4MSXMIT);
		}
	}	
	if (modes & HAL_MODE_108G) {
		ahp.ah_currentRD = rd;
		if (ath_hal_getchannels(&ahp.h, tgchans, IEEE80211_CHAN_MAX, &ntg,
		    HAL_MODE_108G, cc, rd, extendedChanMode) == HAL_OK) {
			calctxpower(&ahp.h, ntg, tgchans, tpcReduction, powerLimit, tgtxpow);
			if (showdfs)
				isdfs |= anychan(tgchans, ntg, IEEE80211_CHAN_DFS);
			if (show4ms)
				is4ms |= anychan(tgchans, ntg, IEEE80211_CHAN_4MSXMIT);
		}
	}
	if (modes & HAL_MODE_HT) {
		ahp.ah_currentRD = rd;
		if (ath_hal_getchannels(&ahp.h, nchans, IEEE80211_CHAN_MAX, &nn,
		    modes & HAL_MODE_HT, cc, rd, extendedChanMode) == HAL_OK) {
			calctxpower(&ahp.h, nn, nchans, tpcReduction, powerLimit, ntxpow);
			if (showdfs)
				isdfs |= anychan(nchans, nn, IEEE80211_CHAN_DFS);
			if (show4ms)
				is4ms |= anychan(nchans, nn, IEEE80211_CHAN_4MSXMIT);
		}
	}

	if (!showall) {
#define	CHECKMODES(_modes, _m)	((_modes & (_m)) == (_m))
		if (CHECKMODES(modes, HAL_MODE_11B|HAL_MODE_11G)) {
			/* b ^= g */
			intersect(bchans, btxpow, &nb, gchans, gtxpow, ng);
		}
		if (CHECKMODES(modes, HAL_MODE_11A|HAL_MODE_TURBO)) {
			/* t ^= a */
			intersect(tchans, ttxpow, &nt, achans, atxpow, na);
		}
		if (CHECKMODES(modes, HAL_MODE_11G|HAL_MODE_108G)) {
			/* tg ^= g */
			intersect(tgchans, tgtxpow, &ntg, gchans, gtxpow, ng);
		}
		if (CHECKMODES(modes, HAL_MODE_11G|HAL_MODE_HT)) {
			/* g ^= n */
			intersect(gchans, gtxpow, &ng, nchans, ntxpow, nn);
		}
		if (CHECKMODES(modes, HAL_MODE_11A|HAL_MODE_HT)) {
			/* a ^= n */
			intersect(achans, atxpow, &na, nchans, ntxpow, nn);
		}
#undef CHECKMODES
	}

	if (modes & HAL_MODE_11G)
		dumpchannels(&ahp.h, ng, gchans, gtxpow);
	if (modes & HAL_MODE_11B)
		dumpchannels(&ahp.h, nb, bchans, btxpow);
	if (modes & HAL_MODE_11A)
		dumpchannels(&ahp.h, na, achans, atxpow);
	if (modes & HAL_MODE_108G)
		dumpchannels(&ahp.h, ntg, tgchans, tgtxpow);
	if (modes & HAL_MODE_TURBO)
		dumpchannels(&ahp.h, nt, tchans, ttxpow);
	if (modes & HAL_MODE_HT)
		dumpchannels(&ahp.h, nn, nchans, ntxpow);
	printf("\n");
	return (0);
}