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
struct ncprange {int ncprange_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct ncprange*,char,int) ; 

void
ncprange_setdefault(struct ncprange *range, int af)
{
  memset(range, '\0', sizeof *range);
  range->ncprange_family = af;
}