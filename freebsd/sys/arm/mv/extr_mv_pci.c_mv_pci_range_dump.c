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
struct mv_pci_range {int /*<<< orphan*/  len; int /*<<< orphan*/  base_parent; int /*<<< orphan*/  base_pci; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
mv_pci_range_dump(struct mv_pci_range *range)
{
#ifdef DEBUG
	printf("\n");
	printf("  base_pci = 0x%08lx\n", range->base_pci);
	printf("  base_par = 0x%08lx\n", range->base_parent);
	printf("  len      = 0x%08lx\n", range->len);
#endif
}