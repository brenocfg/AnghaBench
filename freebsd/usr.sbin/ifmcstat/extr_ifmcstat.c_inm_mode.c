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
typedef  size_t u_int ;

/* Variables and functions */
 size_t MCAST_EXCLUDE ; 
 size_t MCAST_UNDEFINED ; 
 char const** inm_modes ; 

__attribute__((used)) static const char *
inm_mode(u_int mode)
{

	if (mode >= MCAST_UNDEFINED && mode <= MCAST_EXCLUDE)
		return (inm_modes[mode]);
	return (NULL);
}