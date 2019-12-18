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
 int /*<<< orphan*/  BUG () ; 
#define  ESTAR_MODE_DIV_1 132 
#define  ESTAR_MODE_DIV_2 131 
#define  ESTAR_MODE_DIV_4 130 
#define  ESTAR_MODE_DIV_6 129 
#define  ESTAR_MODE_DIV_8 128 
 unsigned long ESTAR_MODE_DIV_MASK ; 

__attribute__((used)) static unsigned long estar_to_divisor(unsigned long estar)
{
	unsigned long ret;

	switch (estar & ESTAR_MODE_DIV_MASK) {
	case ESTAR_MODE_DIV_1:
		ret = 1;
		break;
	case ESTAR_MODE_DIV_2:
		ret = 2;
		break;
	case ESTAR_MODE_DIV_4:
		ret = 4;
		break;
	case ESTAR_MODE_DIV_6:
		ret = 6;
		break;
	case ESTAR_MODE_DIV_8:
		ret = 8;
		break;
	default:
		BUG();
	}

	return ret;
}