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
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct ncprange {int ncprange_family; int /*<<< orphan*/  ncprange_ip6addr; int /*<<< orphan*/  ncprange_ip6width; TYPE_2__ ncprange_ip4mask; TYPE_1__ ncprange_ip4addr; } ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_UNSPEC 128 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int
ncprange_equal(const struct ncprange *range, const struct ncprange *cmp)
{
  if (range->ncprange_family != cmp->ncprange_family)
    return 0;

  switch (range->ncprange_family) {
  case AF_INET:
    if (range->ncprange_ip4addr.s_addr != cmp->ncprange_ip4addr.s_addr)
      return 0;
    return range->ncprange_ip4mask.s_addr == cmp->ncprange_ip4mask.s_addr;

#ifndef NOINET6
  case AF_INET6:
    if (range->ncprange_ip6width != cmp->ncprange_ip6width)
      return 0;
    return !memcmp(&range->ncprange_ip6addr, &cmp->ncprange_ip6addr,
                   sizeof range->ncprange_ip6addr);
#endif

  case AF_UNSPEC:
    return 1;
  }

  return 0;
}