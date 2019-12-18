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
struct target_ops {struct section_table* to_sections_end; struct section_table* to_sections; } ;
struct section_table {scalar_t__ addr; scalar_t__ endaddr; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */

struct section_table *
target_section_by_addr (struct target_ops *target, CORE_ADDR addr)
{
  struct section_table *secp;
  for (secp = target->to_sections;
       secp < target->to_sections_end;
       secp++)
    {
      if (addr >= secp->addr && addr < secp->endaddr)
	return secp;
    }
  return NULL;
}