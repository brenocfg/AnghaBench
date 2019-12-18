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
struct libalias {int /*<<< orphan*/  fireWallField; int /*<<< orphan*/  fireWallFD; } ;
struct ip_fw {int dummy; } ;
struct TYPE_4__ {TYPE_1__* tcp; } ;
struct alias_link {scalar_t__ link_type; TYPE_2__ data; struct libalias* la; } ;
struct TYPE_3__ {int fwhole; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IP_FW_DEL ; 
 scalar_t__ LINK_TCP ; 
 int /*<<< orphan*/  fw_clrfield (struct libalias*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ip_fw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void
ClearFWHole(struct alias_link *lnk)
{
	struct libalias *la;

	la = lnk->la;
	if (lnk->link_type == LINK_TCP) {
		int fwhole = lnk->data.tcp->fwhole;	/* Where is the firewall
							 * hole? */
		struct ip_fw rule;

		if (fwhole < 0)
			return;

		memset(&rule, 0, sizeof rule);	/* useless for ipfw2 */
		while (!setsockopt(la->fireWallFD, IPPROTO_IP, IP_FW_DEL,
		    &fwhole, sizeof fwhole));
		fw_clrfield(la, la->fireWallField, fwhole);
		lnk->data.tcp->fwhole = -1;
	}
}