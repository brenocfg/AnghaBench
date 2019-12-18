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
struct link {int dummy; } ;
struct TYPE_2__ {struct link* link; } ;
struct ipv6cp {TYPE_1__ fsm; } ;

/* Variables and functions */

void
ipv6cp_SetLink(struct ipv6cp *ipv6cp, struct link *l)
{
  ipv6cp->fsm.link = l;
}