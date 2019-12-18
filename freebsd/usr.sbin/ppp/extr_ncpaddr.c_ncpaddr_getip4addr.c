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
struct ncpaddr {scalar_t__ ncpaddr_family; TYPE_1__ ncpaddr_ip4addr; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 

int
ncpaddr_getip4addr(const struct ncpaddr *addr, u_int32_t *ip)
{
  if (addr->ncpaddr_family != AF_INET)
    return 0;
  *ip = addr->ncpaddr_ip4addr.s_addr;
  return 1;
}