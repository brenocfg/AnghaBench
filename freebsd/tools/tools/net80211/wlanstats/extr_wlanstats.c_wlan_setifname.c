#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  i_name; } ;
struct TYPE_3__ {int /*<<< orphan*/  ifr_name; } ;
struct wlanstatfoo_p {TYPE_2__ ireq; TYPE_1__ ifr; } ;
struct wlanstatfoo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
wlan_setifname(struct wlanstatfoo *wf0, const char *ifname)
{
	struct wlanstatfoo_p *wf = (struct wlanstatfoo_p *) wf0;

	strncpy(wf->ifr.ifr_name, ifname, sizeof (wf->ifr.ifr_name));
	strncpy(wf->ireq.i_name, ifname, sizeof (wf->ireq.i_name));
}