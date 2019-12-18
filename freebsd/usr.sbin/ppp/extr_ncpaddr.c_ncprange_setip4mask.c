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
struct ncprange {scalar_t__ ncprange_family; int /*<<< orphan*/  ncprange_ip4width; struct in_addr ncprange_ip4mask; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  mask42bits (struct in_addr) ; 

int
ncprange_setip4mask(struct ncprange *range, struct in_addr mask)
{
  if (range->ncprange_family != AF_INET)
    return 0;
  range->ncprange_ip4mask = mask;
  range->ncprange_ip4width = mask42bits(mask);
  return 1;
}