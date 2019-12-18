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

/* Variables and functions */
 int KNL_MAX_CHANNELS ; 
 char knl_get_mc_route (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void knl_show_mc_route(u32 reg, char *s)
{
	int i;

	for (i = 0; i < KNL_MAX_CHANNELS; i++) {
		s[i*2] = knl_get_mc_route(i, reg) + '0';
		s[i*2+1] = '-';
	}

	s[KNL_MAX_CHANNELS*2 - 1] = '\0';
}