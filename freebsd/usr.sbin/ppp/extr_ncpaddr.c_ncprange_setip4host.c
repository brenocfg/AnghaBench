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
struct TYPE_2__ {scalar_t__ s_addr; } ;
struct in_addr {scalar_t__ s_addr; } ;
struct ncprange {int ncprange_ip4width; TYPE_1__ ncprange_ip4mask; struct in_addr ncprange_ip4addr; int /*<<< orphan*/  ncprange_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ INADDR_ANY ; 
 scalar_t__ INADDR_BROADCAST ; 

void
ncprange_setip4host(struct ncprange *range, struct in_addr from)
{
  range->ncprange_family = AF_INET;
  range->ncprange_ip4addr = from;
  if (from.s_addr == INADDR_ANY) {
    range->ncprange_ip4mask.s_addr = INADDR_ANY;
    range->ncprange_ip4width = 0;
  } else {
    range->ncprange_ip4mask.s_addr = INADDR_BROADCAST;
    range->ncprange_ip4width = 32;
  }
}