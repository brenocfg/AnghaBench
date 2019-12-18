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
struct TYPE_2__ {int /*<<< orphan*/  ad_name; } ;
struct athstatfoo_p {int /*<<< orphan*/  optstats; TYPE_1__ atd; int /*<<< orphan*/  req; } ;
struct athstatfoo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATHSTATS_ANI ; 
 int /*<<< orphan*/  ath_driver_req_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath_driver_req_open (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
ath_setifname(struct athstatfoo *wf0, const char *ifname)
{
	struct athstatfoo_p *wf = (struct athstatfoo_p *) wf0;

	ath_driver_req_close(&wf->req);
	(void) ath_driver_req_open(&wf->req, ifname);
#ifdef ATH_SUPPORT_ANI
	strncpy(wf->atd.ad_name, ifname, sizeof (wf->atd.ad_name));
	wf->optstats |= ATHSTATS_ANI;
#endif
}