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
 scalar_t__ SLC_EXPORT ; 
 scalar_t__ SLC_IMPORT ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ slc_mode ; 

void
slcstate(void)
{
    printf("Special characters are %s values\n",
		slc_mode == SLC_IMPORT ? "remote default" :
		slc_mode == SLC_EXPORT ? "local" :
					 "remote");
}