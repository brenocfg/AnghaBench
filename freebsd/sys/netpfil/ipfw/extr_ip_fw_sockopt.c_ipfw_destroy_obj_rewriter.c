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
 int /*<<< orphan*/  M_IPFW ; 
 int /*<<< orphan*/ * ctl3_rewriters ; 
 scalar_t__ ctl3_rsize ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ipfw_destroy_obj_rewriter()
{

	if (ctl3_rewriters != NULL)
		free(ctl3_rewriters, M_IPFW);
	ctl3_rewriters = NULL;
	ctl3_rsize = 0;
}