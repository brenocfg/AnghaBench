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
typedef  int /*<<< orphan*/  platform_t ;

/* Variables and functions */
 scalar_t__ mp_maxid ; 
 scalar_t__ mp_ncpus ; 
 scalar_t__ platform_get_ncpus () ; 

void
mv_axp_platform_mp_setmaxid(platform_t plat)
{

	mp_ncpus = platform_get_ncpus();
	mp_maxid = mp_ncpus - 1;
}