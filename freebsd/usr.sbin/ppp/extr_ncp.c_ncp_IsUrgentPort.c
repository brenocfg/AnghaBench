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
typedef  scalar_t__ u_short ;
struct port_range {unsigned int nports; scalar_t__* port; } ;

/* Variables and functions */

int
ncp_IsUrgentPort(struct port_range *range, u_short src, u_short dst)
{
  unsigned f;

  for (f = 0; f < range->nports; f++)
    if (range->port[f] == src || range->port[f] == dst)
      return 1;

  return 0;
}