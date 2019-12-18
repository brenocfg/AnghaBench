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
struct in_addr {int dummy; } ;
struct ncprange {scalar_t__ ncprange_family; struct in_addr ncprange_ip4addr; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 

int
ncprange_getip4addr(const struct ncprange *range, struct in_addr *addr)
{
  if (range->ncprange_family != AF_INET)
    return 0;

  *addr = range->ncprange_ip4addr;
  return 1;
}