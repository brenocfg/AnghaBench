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
struct section_addr_info {int num_sections; TYPE_1__* other; } ;
struct TYPE_2__ {struct section_addr_info* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfree (struct section_addr_info*) ; 

extern void
free_section_addr_info (struct section_addr_info *sap)
{
  int idx;

  for (idx = 0; idx < sap->num_sections; idx++)
    if (sap->other[idx].name)
      xfree (sap->other[idx].name);
  xfree (sap);
}