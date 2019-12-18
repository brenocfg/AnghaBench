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
struct symtab_and_line {int dummy; } ;
typedef  int /*<<< orphan*/  asection ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/ * find_pc_overlay (int /*<<< orphan*/ ) ; 
 struct symtab_and_line find_pc_sect_line (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  overlay_mapped_address (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pc_in_unmapped_range (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct symtab_and_line
find_pc_line (CORE_ADDR pc, int notcurrent)
{
  asection *section;

  section = find_pc_overlay (pc);
  if (pc_in_unmapped_range (pc, section))
    pc = overlay_mapped_address (pc, section);
  return find_pc_sect_line (pc, section, notcurrent);
}