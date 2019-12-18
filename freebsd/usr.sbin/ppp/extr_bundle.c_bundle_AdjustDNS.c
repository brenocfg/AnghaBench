#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct in_addr {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  alive; int /*<<< orphan*/  dial; int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;
struct TYPE_5__ {struct in_addr* dns; } ;
struct TYPE_6__ {TYPE_1__ ns; } ;
struct TYPE_7__ {TYPE_2__ ipcp; } ;
struct bundle {TYPE_4__ filter; TYPE_3__ ncp; } ;

/* Variables and functions */
 int /*<<< orphan*/  filter_AdjustAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct in_addr*) ; 

void
bundle_AdjustDNS(struct bundle *bundle)
{
  struct in_addr *dns = bundle->ncp.ipcp.ns.dns;

  filter_AdjustAddr(&bundle->filter.in, NULL, NULL, dns);
  filter_AdjustAddr(&bundle->filter.out, NULL, NULL, dns);
  filter_AdjustAddr(&bundle->filter.dial, NULL, NULL, dns);
  filter_AdjustAddr(&bundle->filter.alive, NULL, NULL, dns);
}