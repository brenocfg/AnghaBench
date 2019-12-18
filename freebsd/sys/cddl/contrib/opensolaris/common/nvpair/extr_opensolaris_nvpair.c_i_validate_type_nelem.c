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
typedef  int uint_t ;
typedef  int data_type_t ;

/* Variables and functions */
#define  DATA_TYPE_BOOLEAN 154 
#define  DATA_TYPE_BOOLEAN_ARRAY 153 
#define  DATA_TYPE_BOOLEAN_VALUE 152 
#define  DATA_TYPE_BYTE 151 
#define  DATA_TYPE_BYTE_ARRAY 150 
#define  DATA_TYPE_DOUBLE 149 
#define  DATA_TYPE_HRTIME 148 
#define  DATA_TYPE_INT16 147 
#define  DATA_TYPE_INT16_ARRAY 146 
#define  DATA_TYPE_INT32 145 
#define  DATA_TYPE_INT32_ARRAY 144 
#define  DATA_TYPE_INT64 143 
#define  DATA_TYPE_INT64_ARRAY 142 
#define  DATA_TYPE_INT8 141 
#define  DATA_TYPE_INT8_ARRAY 140 
#define  DATA_TYPE_NVLIST 139 
#define  DATA_TYPE_NVLIST_ARRAY 138 
#define  DATA_TYPE_STRING 137 
#define  DATA_TYPE_STRING_ARRAY 136 
#define  DATA_TYPE_UINT16 135 
#define  DATA_TYPE_UINT16_ARRAY 134 
#define  DATA_TYPE_UINT32 133 
#define  DATA_TYPE_UINT32_ARRAY 132 
#define  DATA_TYPE_UINT64 131 
#define  DATA_TYPE_UINT64_ARRAY 130 
#define  DATA_TYPE_UINT8 129 
#define  DATA_TYPE_UINT8_ARRAY 128 
 int EINVAL ; 

__attribute__((used)) static int
i_validate_type_nelem(data_type_t type, uint_t nelem)
{
	switch (type) {
	case DATA_TYPE_BOOLEAN:
		if (nelem != 0)
			return (EINVAL);
		break;
	case DATA_TYPE_BOOLEAN_VALUE:
	case DATA_TYPE_BYTE:
	case DATA_TYPE_INT8:
	case DATA_TYPE_UINT8:
	case DATA_TYPE_INT16:
	case DATA_TYPE_UINT16:
	case DATA_TYPE_INT32:
	case DATA_TYPE_UINT32:
	case DATA_TYPE_INT64:
	case DATA_TYPE_UINT64:
	case DATA_TYPE_STRING:
	case DATA_TYPE_HRTIME:
	case DATA_TYPE_NVLIST:
#if !defined(_KERNEL)
	case DATA_TYPE_DOUBLE:
#endif
		if (nelem != 1)
			return (EINVAL);
		break;
	case DATA_TYPE_BOOLEAN_ARRAY:
	case DATA_TYPE_BYTE_ARRAY:
	case DATA_TYPE_INT8_ARRAY:
	case DATA_TYPE_UINT8_ARRAY:
	case DATA_TYPE_INT16_ARRAY:
	case DATA_TYPE_UINT16_ARRAY:
	case DATA_TYPE_INT32_ARRAY:
	case DATA_TYPE_UINT32_ARRAY:
	case DATA_TYPE_INT64_ARRAY:
	case DATA_TYPE_UINT64_ARRAY:
	case DATA_TYPE_STRING_ARRAY:
	case DATA_TYPE_NVLIST_ARRAY:
		/* we allow arrays with 0 elements */
		break;
	default:
		return (EINVAL);
	}
	return (0);
}