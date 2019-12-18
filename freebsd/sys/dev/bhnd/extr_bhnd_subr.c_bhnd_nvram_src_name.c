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
typedef  int bhnd_nvram_src ;

/* Variables and functions */
#define  BHND_NVRAM_SRC_FLASH 131 
#define  BHND_NVRAM_SRC_OTP 130 
#define  BHND_NVRAM_SRC_SPROM 129 
#define  BHND_NVRAM_SRC_UNKNOWN 128 

const char *
bhnd_nvram_src_name(bhnd_nvram_src nvram_src)
{
	switch (nvram_src) {
	case BHND_NVRAM_SRC_FLASH:
		return ("flash");
	case BHND_NVRAM_SRC_OTP:
		return ("OTP");
	case BHND_NVRAM_SRC_SPROM:
		return ("SPROM");
	case BHND_NVRAM_SRC_UNKNOWN:
		return ("none");
	default:
		return ("unknown");
	}
}