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
struct ncprange {int ncprange_family; int /*<<< orphan*/  ncprange_ip6addr; int /*<<< orphan*/  ncprange_ip4addr; } ;
struct ncpaddr {int ncpaddr_family; int /*<<< orphan*/  ncpaddr_ip6addr; int /*<<< orphan*/  ncpaddr_ip4addr; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 

int
ncprange_getaddr(const struct ncprange *range, struct ncpaddr *addr)
{
  switch (range->ncprange_family) {
  case AF_INET:
    addr->ncpaddr_family = AF_INET;
    addr->ncpaddr_ip4addr = range->ncprange_ip4addr;
    return 1;
#ifndef NOINET6
  case AF_INET6:
    addr->ncpaddr_family = AF_INET6;
    addr->ncpaddr_ip6addr =  range->ncprange_ip6addr;
    return 1;
#endif
  }

  return 0;
}