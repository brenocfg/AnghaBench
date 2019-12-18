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
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct ncpaddr {TYPE_1__ ncpaddr_ip4addr; int /*<<< orphan*/  ncpaddr_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 

void
ncpaddr_setip4addr(struct ncpaddr *addr, u_int32_t ip)
{
  addr->ncpaddr_family = AF_INET;
  addr->ncpaddr_ip4addr.s_addr = ip;
}