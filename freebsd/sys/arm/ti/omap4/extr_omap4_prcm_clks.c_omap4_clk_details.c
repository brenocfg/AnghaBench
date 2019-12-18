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
struct omap4_clk_details {scalar_t__ id; } ;
typedef  scalar_t__ clk_ident_t ;

/* Variables and functions */
 scalar_t__ INVALID_CLK_IDENT ; 
 struct omap4_clk_details* g_omap4_clk_details ; 

__attribute__((used)) static struct omap4_clk_details*
omap4_clk_details(clk_ident_t id)
{
	struct omap4_clk_details *walker;

	for (walker = g_omap4_clk_details; walker->id != INVALID_CLK_IDENT; walker++) {
		if (id == walker->id)
			return (walker);
	}

	return NULL;
}