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
struct TYPE_2__ {int /*<<< orphan*/  ifr_name; } ;
struct mwlstatfoo_p {TYPE_1__ ifr; } ;
struct mwlstatfoo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
mwl_setifname(struct mwlstatfoo *wf0, const char *ifname)
{
	struct mwlstatfoo_p *wf = (struct mwlstatfoo_p *) wf0;

	strncpy(wf->ifr.ifr_name, ifname, sizeof (wf->ifr.ifr_name));
}