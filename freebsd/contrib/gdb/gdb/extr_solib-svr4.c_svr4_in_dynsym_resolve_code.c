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
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ in_plt_section (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ interp_plt_sect_high ; 
 scalar_t__ interp_plt_sect_low ; 
 scalar_t__ interp_text_sect_high ; 
 scalar_t__ interp_text_sect_low ; 

__attribute__((used)) static int
svr4_in_dynsym_resolve_code (CORE_ADDR pc)
{
  return ((pc >= interp_text_sect_low && pc < interp_text_sect_high)
	  || (pc >= interp_plt_sect_low && pc < interp_plt_sect_high)
	  || in_plt_section (pc, NULL));
}