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
struct ncprange {int ncprange_family; struct in_addr ncprange_ip4mask; } ;

/* Variables and functions */
#define  AF_INET 128 

int
ncprange_getip4mask(const struct ncprange *range, struct in_addr *mask)
{
  switch (range->ncprange_family) {
  case AF_INET:
    *mask = range->ncprange_ip4mask;
    return 1;
  }

  return 0;
}