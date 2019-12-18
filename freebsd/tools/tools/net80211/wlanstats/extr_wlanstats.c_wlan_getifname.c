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
struct TYPE_2__ {char const* ifr_name; } ;
struct wlanstatfoo_p {TYPE_1__ ifr; } ;
struct wlanstatfoo {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static const char *
wlan_getifname(struct wlanstatfoo *wf0)
{
	struct wlanstatfoo_p *wf = (struct wlanstatfoo_p *) wf0;

	return wf->ifr.ifr_name;
}