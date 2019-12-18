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
typedef  int /*<<< orphan*/  asection ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ overlay_debugging ; 
 int /*<<< orphan*/  overlay_unmapped_address (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ section_is_mapped (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  section_is_overlay (int /*<<< orphan*/ *) ; 

CORE_ADDR
symbol_overlayed_address (CORE_ADDR address, asection *section)
{
  if (overlay_debugging)
    {
      /* If the symbol has no section, just return its regular address. */
      if (section == 0)
	return address;
      /* If the symbol's section is not an overlay, just return its address */
      if (!section_is_overlay (section))
	return address;
      /* If the symbol's section is mapped, just return its address */
      if (section_is_mapped (section))
	return address;
      /*
       * HOWEVER: if the symbol is in an overlay section which is NOT mapped,
       * then return its LOADED address rather than its vma address!!
       */
      return overlay_unmapped_address (address, section);
    }
  return address;
}