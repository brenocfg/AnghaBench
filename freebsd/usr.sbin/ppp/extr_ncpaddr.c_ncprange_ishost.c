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
struct ncprange {int ncprange_family; int ncprange_ip4width; int ncprange_ip6width; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 

int
ncprange_ishost(const struct ncprange *range)
{
  switch (range->ncprange_family) {
  case AF_INET:
    return range->ncprange_ip4width == 32;
#ifndef NOINET6
  case AF_INET6:
    return range->ncprange_ip6width == 128;
#endif
  }

  return (0);
}