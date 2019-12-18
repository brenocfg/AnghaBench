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
#define  VAS_COP_TYPE_842 133 
#define  VAS_COP_TYPE_842_HIPRI 132 
#define  VAS_COP_TYPE_FAULT 131 
#define  VAS_COP_TYPE_FTW 130 
#define  VAS_COP_TYPE_GZIP 129 
#define  VAS_COP_TYPE_GZIP_HIPRI 128 

__attribute__((used)) static char *cop_to_str(int cop)
{
	switch (cop) {
	case VAS_COP_TYPE_FAULT:	return "Fault";
	case VAS_COP_TYPE_842:		return "NX-842 Normal Priority";
	case VAS_COP_TYPE_842_HIPRI:	return "NX-842 High Priority";
	case VAS_COP_TYPE_GZIP:		return "NX-GZIP Normal Priority";
	case VAS_COP_TYPE_GZIP_HIPRI:	return "NX-GZIP High Priority";
	case VAS_COP_TYPE_FTW:		return "Fast Thread-wakeup";
	default:			return "Unknown";
	}
}