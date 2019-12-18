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
struct symtab {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  find_pc_mapped_section (int /*<<< orphan*/ ) ; 
 struct symtab* find_pc_sect_symtab (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct symtab *
find_pc_symtab (CORE_ADDR pc)
{
  return find_pc_sect_symtab (pc, find_pc_mapped_section (pc));
}