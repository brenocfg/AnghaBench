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
struct targ {TYPE_1__* g; } ;
struct pkt {int dummy; } ;
struct TYPE_2__ {scalar_t__ af; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  update_ip (struct pkt*,struct targ*) ; 
 int /*<<< orphan*/  update_ip6 (struct pkt*,struct targ*) ; 

__attribute__((used)) static void
update_addresses(struct pkt *pkt, struct targ *t)
{

	if (t->g->af == AF_INET)
		update_ip(pkt, t);
	else
		update_ip6(pkt, t);
}