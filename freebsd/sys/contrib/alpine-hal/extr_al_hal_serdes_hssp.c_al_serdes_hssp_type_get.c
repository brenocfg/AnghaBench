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
typedef  enum al_serdes_type { ____Placeholder_al_serdes_type } al_serdes_type ;

/* Variables and functions */
 int AL_SRDS_TYPE_HSSP ; 

__attribute__((used)) static enum al_serdes_type al_serdes_hssp_type_get(void)
{
	return AL_SRDS_TYPE_HSSP;
}