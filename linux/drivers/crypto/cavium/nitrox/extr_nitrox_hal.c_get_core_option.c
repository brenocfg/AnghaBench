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
typedef  int u8 ;

/* Variables and functions */
 int AE_MAX_CORES ; 
#define  SE_MAX_CORES 128 

__attribute__((used)) static const char *get_core_option(u8 se_cores, u8 ae_cores)
{
	const char *option = "";

	if (ae_cores == AE_MAX_CORES) {
		switch (se_cores) {
		case SE_MAX_CORES:
			option = "60";
			break;
		case 40:
			option = "60s";
			break;
		}
	} else if (ae_cores == (AE_MAX_CORES / 2)) {
		option = "30";
	} else {
		option = "60i";
	}

	return option;
}