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
struct g_part_table {int gpt_sectors; } ;
struct g_part_parms {int gpp_index; int gpp_start; } ;
typedef  enum g_part_ctl { ____Placeholder_g_part_ctl } g_part_ctl ;

/* Variables and functions */
 int ECANCELED ; 
 int G_PART_CTL_ADD ; 
 int G_PART_CTL_DESTROY ; 

__attribute__((used)) static int
g_part_ebr_precheck(struct g_part_table *table, enum g_part_ctl req,
    struct g_part_parms *gpp)
{
#if defined(GEOM_PART_EBR_COMPAT)
	if (req == G_PART_CTL_DESTROY)
		return (0);
	return (ECANCELED);
#else
	/*
	 * The index is a function of the start of the partition.
	 * This is not something the user can override, nor is it
	 * something the common code will do right. We can set the
	 * index now so that we get what we need.
	 */
	if (req == G_PART_CTL_ADD)
		gpp->gpp_index = (gpp->gpp_start / table->gpt_sectors) + 1;
	return (0);
#endif
}