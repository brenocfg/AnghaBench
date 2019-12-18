#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int uint32_t ;
typedef  size_t uint16_t ;
struct ieee80211_rate_table {size_t* rateCodeToIndex; size_t rateCount; TYPE_1__* info; } ;
struct ieee80211_frame {int dummy; } ;
struct TYPE_2__ {size_t dot11Rate; } ;

/* Variables and functions */
 int IEEE80211_CRC_LEN ; 
 size_t IEEE80211_RATE_BASIC ; 
 int LLC_SNAPFRAMELEN ; 
 float atof (char*) ; 
 int checkpreamble (struct ieee80211_rate_table const*,size_t,int,int) ; 
 int /*<<< orphan*/  errx (int,char*,char const*,...) ; 
 int getopt (int,char**,char*) ; 
 size_t ieee80211_compute_duration (struct ieee80211_rate_table const*,int,size_t,int) ; 
 int /*<<< orphan*/  ieee80211_phy_init () ; 
 struct ieee80211_rate_table* mode2table (char const*) ; 
 char* optarg ; 
 int /*<<< orphan*/  printf (char*,size_t,int,char*,char*) ; 
 char* srate (size_t) ; 
 int strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (char*) ; 

int
main(int argc, char *argv[])
{
	const struct ieee80211_rate_table *rt;
	const char *mode;
	uint32_t frameLen;
	uint16_t rate;
	uint16_t time;
	uint8_t rix;
	int ch, allrates, isShortPreamble, isShort;
	float frate;

	ieee80211_phy_init();

	mode = "11g";
	isShortPreamble = 0;
	frameLen = 1500
		 + sizeof(struct ieee80211_frame)
		 + LLC_SNAPFRAMELEN
		 + IEEE80211_CRC_LEN
		 ;
	rate = 2*54;
	allrates = 0;
	while ((ch = getopt(argc, argv, "al:m:r:s")) != -1) {
		switch (ch) {
		case 'a':
			allrates = 1;
			break;
		case 'l':
			frameLen = strtoul(optarg, NULL, 0);
			break;
		case 'm':
			mode = optarg;
			break;
		case 'r':
			frate = atof(optarg);
			rate = (int) 2*frate;
			break;
		case 's':
			isShortPreamble = 1;
			break;
		default:
			usage(argv[0]);
			break;
		}
	}
	rt = mode2table(mode);
	if (rt == NULL)
		errx(-1, "unknown mode %s", mode);
	if (!allrates) {
		rix = rt->rateCodeToIndex[rate];
		if (rix == (uint8_t) -1)
			errx(-1, "rate %s not valid for mode %s", srate(rate), mode);
		isShort = checkpreamble(rt, rix, isShortPreamble, 1);

		time = ieee80211_compute_duration(rt, frameLen, rate, isShort);
		printf("%u usec to send %u bytes @ %s Mb/s, %s preamble\n",
		    time, frameLen, srate(rate),
		    isShort ? "short" : "long");
	} else {
		for (rix = 0; rix < rt->rateCount; rix++) {
			rate = rt->info[rix].dot11Rate &~ IEEE80211_RATE_BASIC;
			isShort = checkpreamble(rt, rix, isShortPreamble, 0);
			time = ieee80211_compute_duration(rt, frameLen, rate,
			    isShort);
			printf("%u usec to send %u bytes @ %s Mb/s, %s preamble\n",
			    time, frameLen, srate(rate),
			    isShort ? "short" : "long");
		}
	}
	return 0;
}