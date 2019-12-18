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
struct sglist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  agp_intel_gtt_unmap_memory (int /*<<< orphan*/ ,struct sglist*) ; 
 int /*<<< orphan*/  intel_agp ; 

void
intel_gtt_unmap_memory(struct sglist *sg_list)
{

	agp_intel_gtt_unmap_memory(intel_agp, sg_list);
}