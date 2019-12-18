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
struct collection_list {int* regs_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,unsigned int) ; 
 scalar_t__ info_verbose ; 
 int /*<<< orphan*/  printf_filtered (char*,unsigned int) ; 

__attribute__((used)) static void
add_register (struct collection_list *collection, unsigned int regno)
{
  if (info_verbose)
    printf_filtered ("collect register %d\n", regno);
  if (regno > (8 * sizeof (collection->regs_mask)))
    error ("Internal: register number %d too large for tracepoint",
	   regno);
  collection->regs_mask[regno / 8] |= 1 << (regno % 8);
}