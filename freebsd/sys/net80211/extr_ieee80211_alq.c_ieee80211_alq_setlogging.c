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
struct ieee80211_alq_rec {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  td_ucred; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALQ_DEFAULT_CMODE ; 
 int /*<<< orphan*/  alq_close (int /*<<< orphan*/ *) ; 
 int alq_open (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/ * ieee80211_alq ; 
 char* ieee80211_alq_logfile ; 
 scalar_t__ ieee80211_alq_logged ; 
 scalar_t__ ieee80211_alq_lost ; 
 int /*<<< orphan*/  ieee80211_alq_qsize ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
ieee80211_alq_setlogging(int enable)
{
	int error;

	if (enable) {
		if (ieee80211_alq)
			alq_close(ieee80211_alq);

		error = alq_open(&ieee80211_alq,
		    ieee80211_alq_logfile,
		    curthread->td_ucred,
		    ALQ_DEFAULT_CMODE,
		    ieee80211_alq_qsize, 0);
		ieee80211_alq_lost = 0;
		ieee80211_alq_logged = 0;
		printf("net80211: logging to %s enabled; "
		    "struct size %d bytes\n",
		    ieee80211_alq_logfile,
		    (int) sizeof(struct ieee80211_alq_rec));
	} else {
		if (ieee80211_alq)
			alq_close(ieee80211_alq);
		ieee80211_alq = NULL;
		printf("net80211: logging disabled\n");
		error = 0;
	}
	return (error);
}