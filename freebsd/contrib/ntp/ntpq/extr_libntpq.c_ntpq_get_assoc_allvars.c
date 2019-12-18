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
typedef  int /*<<< orphan*/  associd_t ;

/* Variables and functions */
 int ntpq_get_assoc_clockvars (int /*<<< orphan*/ ) ; 
 int ntpq_get_assoc_peervars (int /*<<< orphan*/ ) ; 

int  ntpq_get_assoc_allvars( associd_t associd  )
{
	return ntpq_get_assoc_peervars ( associd ) &
	       ntpq_get_assoc_clockvars( associd );
}