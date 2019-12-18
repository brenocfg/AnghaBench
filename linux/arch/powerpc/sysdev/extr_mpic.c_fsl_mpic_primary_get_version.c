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
typedef  int /*<<< orphan*/  u32 ;
struct mpic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsl_mpic_get_version (struct mpic*) ; 
 struct mpic* mpic_primary ; 

u32 fsl_mpic_primary_get_version(void)
{
	struct mpic *mpic = mpic_primary;

	if (mpic)
		return fsl_mpic_get_version(mpic);

	return 0;
}