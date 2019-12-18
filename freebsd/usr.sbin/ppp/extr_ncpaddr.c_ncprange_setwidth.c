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
struct ncprange {int ncprange_family; int ncprange_ip4width; int ncprange_ip6width; int /*<<< orphan*/  ncprange_ip4mask; } ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_UNSPEC 128 
 int /*<<< orphan*/  bits2mask4 (int) ; 

int
ncprange_setwidth(struct ncprange *range, int width)
{
  switch (range->ncprange_family) {
  case AF_INET:
    if (width < 0 || width > 32)
      break;
    range->ncprange_ip4width = width;
    range->ncprange_ip4mask = bits2mask4(width);
    break;

#ifndef NOINET6
  case AF_INET6:
    if (width < 0 || width > 128)
      break;
    range->ncprange_ip6width = width;
    break;
#endif

  case AF_UNSPEC:
    return 1;
  }

  return 0;
}