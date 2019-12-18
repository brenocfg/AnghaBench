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
struct ipv6cp {scalar_t__ my_reject; scalar_t__ his_reject; int /*<<< orphan*/  hisaddr; int /*<<< orphan*/  myaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ncpaddr_init (int /*<<< orphan*/ *) ; 

void
ipv6cp_Setup(struct ipv6cp *ipv6cp)
{
  ncpaddr_init(&ipv6cp->myaddr);
  ncpaddr_init(&ipv6cp->hisaddr);

  ipv6cp->his_reject = 0;
  ipv6cp->my_reject = 0;
}