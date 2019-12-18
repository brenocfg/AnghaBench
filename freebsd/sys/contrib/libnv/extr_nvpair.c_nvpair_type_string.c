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
#define  NV_TYPE_BINARY 139 
#define  NV_TYPE_BOOL 138 
#define  NV_TYPE_BOOL_ARRAY 137 
#define  NV_TYPE_DESCRIPTOR 136 
#define  NV_TYPE_DESCRIPTOR_ARRAY 135 
#define  NV_TYPE_NULL 134 
#define  NV_TYPE_NUMBER 133 
#define  NV_TYPE_NUMBER_ARRAY 132 
#define  NV_TYPE_NVLIST 131 
#define  NV_TYPE_NVLIST_ARRAY 130 
#define  NV_TYPE_STRING 129 
#define  NV_TYPE_STRING_ARRAY 128 

const char *
nvpair_type_string(int type)
{

	switch (type) {
	case NV_TYPE_NULL:
		return ("NULL");
	case NV_TYPE_BOOL:
		return ("BOOL");
	case NV_TYPE_NUMBER:
		return ("NUMBER");
	case NV_TYPE_STRING:
		return ("STRING");
	case NV_TYPE_NVLIST:
		return ("NVLIST");
	case NV_TYPE_DESCRIPTOR:
		return ("DESCRIPTOR");
	case NV_TYPE_BINARY:
		return ("BINARY");
	case NV_TYPE_BOOL_ARRAY:
		return ("BOOL ARRAY");
	case NV_TYPE_NUMBER_ARRAY:
		return ("NUMBER ARRAY");
	case NV_TYPE_STRING_ARRAY:
		return ("STRING ARRAY");
	case NV_TYPE_NVLIST_ARRAY:
		return ("NVLIST ARRAY");
	case NV_TYPE_DESCRIPTOR_ARRAY:
		return ("DESCRIPTOR ARRAY");
	default:
		return ("<UNKNOWN>");
	}
}