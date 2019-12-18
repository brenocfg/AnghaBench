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
struct ncprange {int ncprange_family; int /*<<< orphan*/  ncprange_ip6width; int /*<<< orphan*/  ncprange_ip6addr; int /*<<< orphan*/  ncprange_ip4width; int /*<<< orphan*/  ncprange_ip4mask; int /*<<< orphan*/  ncprange_ip4addr; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int AF_UNSPEC ; 

void
ncprange_copy(struct ncprange *range, const struct ncprange *from)
{
  switch (from->ncprange_family) {
  case AF_INET:
    range->ncprange_family = AF_INET;
    range->ncprange_ip4addr = from->ncprange_ip4addr;
    range->ncprange_ip4mask = from->ncprange_ip4mask;
    range->ncprange_ip4width = from->ncprange_ip4width;
    break;

#ifndef NOINET6
  case AF_INET6:
    range->ncprange_family = AF_INET6;
    range->ncprange_ip6addr = from->ncprange_ip6addr;
    range->ncprange_ip6width = from->ncprange_ip6width;
    break;
#endif

  default:
    range->ncprange_family = AF_UNSPEC;
  }
}