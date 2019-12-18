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
#define  IPW_RATE_DS1 131 
#define  IPW_RATE_DS11 130 
#define  IPW_RATE_DS2 129 
#define  IPW_RATE_DS5 128 

__attribute__((used)) static int
ipw_cvtrate(int ipwrate)
{
	switch (ipwrate) {
	case IPW_RATE_DS1:	return 2;
	case IPW_RATE_DS2:	return 4;
	case IPW_RATE_DS5:	return 11;
	case IPW_RATE_DS11:	return 22;
	}
	return 0;
}