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
struct ncprange {int ncprange_family; int ncprange_ip4width; int ncprange_ip6width; int /*<<< orphan*/  ncprange_ip6addr; TYPE_2__ ncprange_ip4mask; TYPE_1__ ncprange_ip4addr; } ;
struct ncpaddr {int ncpaddr_family; int /*<<< orphan*/  ncpaddr_ip6addr; TYPE_1__ ncpaddr_ip4addr; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int AF_UNSPEC ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  INADDR_BROADCAST ; 

void
ncprange_sethost(struct ncprange *range, const struct ncpaddr *from)
{
  switch (from->ncpaddr_family) {
  case AF_INET:
    range->ncprange_family = AF_INET;
    range->ncprange_ip4addr = from->ncpaddr_ip4addr;
    if (from->ncpaddr_ip4addr.s_addr == INADDR_ANY) {
      range->ncprange_ip4mask.s_addr = INADDR_ANY;
      range->ncprange_ip4width = 0;
    } else {
      range->ncprange_ip4mask.s_addr = INADDR_BROADCAST;
      range->ncprange_ip4width = 32;
    }
    break;

#ifndef NOINET6
  case AF_INET6:
    range->ncprange_family = AF_INET6;
    range->ncprange_ip6addr = from->ncpaddr_ip6addr;
    range->ncprange_ip6width = 128;
    break;
#endif

  default:
    range->ncprange_family = AF_UNSPEC;
  }
}