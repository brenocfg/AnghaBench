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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int u_int ;
struct timecounter {int tc_frequency; int tc_counter_mask; int tc_quality; char* tc_name; int /*<<< orphan*/  (* tc_get_timecount ) (struct timecounter*) ;struct timecounter* tc_next; } ;
struct sysctl_oid {int dummy; } ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int /*<<< orphan*/  CTLFLAG_RW ; 
 int CTLTYPE_U64 ; 
 int CTLTYPE_UINT ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int*,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid* SYSCTL_ADD_NODE_WITH_LABEL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct timecounter*,int,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  SYSCTL_STATIC_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _kern_timecounter_tc ; 
 scalar_t__ bootverbose ; 
 int hz ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stub1 (struct timecounter*) ; 
 int /*<<< orphan*/  stub2 (struct timecounter*) ; 
 int /*<<< orphan*/  sysctl_kern_timecounter_freq ; 
 int /*<<< orphan*/  sysctl_kern_timecounter_get ; 
 scalar_t__ tc_chosen ; 
 struct timecounter* timecounter ; 
 struct timecounter* timecounters ; 

void
tc_init(struct timecounter *tc)
{
	u_int u;
	struct sysctl_oid *tc_root;

	u = tc->tc_frequency / tc->tc_counter_mask;
	/* XXX: We need some margin here, 10% is a guess */
	u *= 11;
	u /= 10;
	if (u > hz && tc->tc_quality >= 0) {
		tc->tc_quality = -2000;
		if (bootverbose) {
			printf("Timecounter \"%s\" frequency %ju Hz",
			    tc->tc_name, (uintmax_t)tc->tc_frequency);
			printf(" -- Insufficient hz, needs at least %u\n", u);
		}
	} else if (tc->tc_quality >= 0 || bootverbose) {
		printf("Timecounter \"%s\" frequency %ju Hz quality %d\n",
		    tc->tc_name, (uintmax_t)tc->tc_frequency,
		    tc->tc_quality);
	}

	tc->tc_next = timecounters;
	timecounters = tc;
	/*
	 * Set up sysctl tree for this counter.
	 */
	tc_root = SYSCTL_ADD_NODE_WITH_LABEL(NULL,
	    SYSCTL_STATIC_CHILDREN(_kern_timecounter_tc), OID_AUTO, tc->tc_name,
	    CTLFLAG_RW, 0, "timecounter description", "timecounter");
	SYSCTL_ADD_UINT(NULL, SYSCTL_CHILDREN(tc_root), OID_AUTO,
	    "mask", CTLFLAG_RD, &(tc->tc_counter_mask), 0,
	    "mask for implemented bits");
	SYSCTL_ADD_PROC(NULL, SYSCTL_CHILDREN(tc_root), OID_AUTO,
	    "counter", CTLTYPE_UINT | CTLFLAG_RD, tc, sizeof(*tc),
	    sysctl_kern_timecounter_get, "IU", "current timecounter value");
	SYSCTL_ADD_PROC(NULL, SYSCTL_CHILDREN(tc_root), OID_AUTO,
	    "frequency", CTLTYPE_U64 | CTLFLAG_RD, tc, sizeof(*tc),
	     sysctl_kern_timecounter_freq, "QU", "timecounter frequency");
	SYSCTL_ADD_INT(NULL, SYSCTL_CHILDREN(tc_root), OID_AUTO,
	    "quality", CTLFLAG_RD, &(tc->tc_quality), 0,
	    "goodness of time counter");
	/*
	 * Do not automatically switch if the current tc was specifically
	 * chosen.  Never automatically use a timecounter with negative quality.
	 * Even though we run on the dummy counter, switching here may be
	 * worse since this timecounter may not be monotonic.
	 */
	if (tc_chosen)
		return;
	if (tc->tc_quality < 0)
		return;
	if (tc->tc_quality < timecounter->tc_quality)
		return;
	if (tc->tc_quality == timecounter->tc_quality &&
	    tc->tc_frequency < timecounter->tc_frequency)
		return;
	(void)tc->tc_get_timecount(tc);
	(void)tc->tc_get_timecount(tc);
	timecounter = tc;
}