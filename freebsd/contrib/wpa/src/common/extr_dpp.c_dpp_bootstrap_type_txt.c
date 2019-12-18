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
typedef  enum dpp_bootstrap_type { ____Placeholder_dpp_bootstrap_type } dpp_bootstrap_type ;

/* Variables and functions */
#define  DPP_BOOTSTRAP_PKEX 129 
#define  DPP_BOOTSTRAP_QR_CODE 128 

const char * dpp_bootstrap_type_txt(enum dpp_bootstrap_type type)
{
	switch (type) {
	case DPP_BOOTSTRAP_QR_CODE:
		return "QRCODE";
	case DPP_BOOTSTRAP_PKEX:
		return "PKEX";
	}
	return "??";
}