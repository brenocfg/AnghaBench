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
typedef  int /*<<< orphan*/  u_int ;
struct sglist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  agp_intel_gtt_insert_sg_entries (int /*<<< orphan*/ ,struct sglist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_agp ; 

void
intel_gtt_insert_sg_entries(struct sglist *sg_list, u_int first_entry,
    u_int flags)
{

	agp_intel_gtt_insert_sg_entries(intel_agp, sg_list, first_entry, flags);
}