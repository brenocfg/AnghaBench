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

/* Variables and functions */
 int /*<<< orphan*/  V_pf_frag_z ; 
 int /*<<< orphan*/  V_pf_frent_z ; 
 int /*<<< orphan*/  V_pf_state_scrub_z ; 
 int /*<<< orphan*/  uma_zdestroy (int /*<<< orphan*/ ) ; 

void
pf_normalize_cleanup(void)
{

	uma_zdestroy(V_pf_state_scrub_z);
	uma_zdestroy(V_pf_frent_z);
	uma_zdestroy(V_pf_frag_z);
}