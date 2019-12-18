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
typedef  int uint32_t ;

/* Variables and functions */
#define  CHIPC_F6_2 133 
#define  CHIPC_F6_3 132 
#define  CHIPC_F6_4 131 
#define  CHIPC_F6_5 130 
#define  CHIPC_F6_6 129 
#define  CHIPC_F6_7 128 

__attribute__((used)) static uint32_t
bhnd_pwrctl_factor6(uint32_t x)
{
	switch (x) {
	case CHIPC_F6_2:	
		return (2);
	case CHIPC_F6_3:	
		return (3);
	case CHIPC_F6_4:	
		return (4);
	case CHIPC_F6_5:	
		return (5);
	case CHIPC_F6_6:
		return (6);
	case CHIPC_F6_7:
		return (7);
	default:
		return (0);
	}
}