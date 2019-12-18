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
struct openpic {scalar_t__ num_mmio_regions; struct mem_reg const** mmio_regions; } ;
struct mem_reg {int dummy; } ;

/* Variables and functions */
 scalar_t__ MAX_MMIO_REGIONS ; 
 int /*<<< orphan*/  WARN (int,char*) ; 

__attribute__((used)) static void add_mmio_region(struct openpic *opp, const struct mem_reg *mr)
{
	if (opp->num_mmio_regions >= MAX_MMIO_REGIONS) {
		WARN(1, "kvm mpic: too many mmio regions\n");
		return;
	}

	opp->mmio_regions[opp->num_mmio_regions++] = mr;
}