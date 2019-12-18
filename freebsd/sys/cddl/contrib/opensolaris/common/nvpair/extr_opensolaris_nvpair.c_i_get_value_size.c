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
typedef  size_t uint_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  uchar_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  int /*<<< orphan*/  hrtime_t ;
typedef  int data_type_t ;
typedef  int /*<<< orphan*/  boolean_t ;

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
 int INT32_MAX ; 
 int NV_ALIGN (int) ; 
 scalar_t__ i_validate_type_nelem (int,size_t) ; 
 int /*<<< orphan*/  strlen (char* const) ; 

__attribute__((used)) static int
i_get_value_size(data_type_t type, const void *data, uint_t nelem)
{
	uint64_t value_sz;

	if (i_validate_type_nelem(type, nelem) != 0)
		return (-1);

	/* Calculate required size for holding value */
	switch (type) {
	case DATA_TYPE_BOOLEAN:
		value_sz = 0;
		break;
	case DATA_TYPE_BOOLEAN_VALUE:
		value_sz = sizeof (boolean_t);
		break;
	case DATA_TYPE_BYTE:
		value_sz = sizeof (uchar_t);
		break;
	case DATA_TYPE_INT8:
		value_sz = sizeof (int8_t);
		break;
	case DATA_TYPE_UINT8:
		value_sz = sizeof (uint8_t);
		break;
	case DATA_TYPE_INT16:
		value_sz = sizeof (int16_t);
		break;
	case DATA_TYPE_UINT16:
		value_sz = sizeof (uint16_t);
		break;
	case DATA_TYPE_INT32:
		value_sz = sizeof (int32_t);
		break;
	case DATA_TYPE_UINT32:
		value_sz = sizeof (uint32_t);
		break;
	case DATA_TYPE_INT64:
		value_sz = sizeof (int64_t);
		break;
	case DATA_TYPE_UINT64:
		value_sz = sizeof (uint64_t);
		break;
#if !defined(_KERNEL)
	case DATA_TYPE_DOUBLE:
		value_sz = sizeof (double);
		break;
#endif
	case DATA_TYPE_STRING:
		if (data == NULL)
			value_sz = 0;
		else
			value_sz = strlen(data) + 1;
		break;
	case DATA_TYPE_BOOLEAN_ARRAY:
		value_sz = (uint64_t)nelem * sizeof (boolean_t);
		break;
	case DATA_TYPE_BYTE_ARRAY:
		value_sz = (uint64_t)nelem * sizeof (uchar_t);
		break;
	case DATA_TYPE_INT8_ARRAY:
		value_sz = (uint64_t)nelem * sizeof (int8_t);
		break;
	case DATA_TYPE_UINT8_ARRAY:
		value_sz = (uint64_t)nelem * sizeof (uint8_t);
		break;
	case DATA_TYPE_INT16_ARRAY:
		value_sz = (uint64_t)nelem * sizeof (int16_t);
		break;
	case DATA_TYPE_UINT16_ARRAY:
		value_sz = (uint64_t)nelem * sizeof (uint16_t);
		break;
	case DATA_TYPE_INT32_ARRAY:
		value_sz = (uint64_t)nelem * sizeof (int32_t);
		break;
	case DATA_TYPE_UINT32_ARRAY:
		value_sz = (uint64_t)nelem * sizeof (uint32_t);
		break;
	case DATA_TYPE_INT64_ARRAY:
		value_sz = (uint64_t)nelem * sizeof (int64_t);
		break;
	case DATA_TYPE_UINT64_ARRAY:
		value_sz = (uint64_t)nelem * sizeof (uint64_t);
		break;
	case DATA_TYPE_STRING_ARRAY:
		value_sz = (uint64_t)nelem * sizeof (uint64_t);

		if (data != NULL) {
			char *const *strs = data;
			uint_t i;

			/* no alignment requirement for strings */
			for (i = 0; i < nelem; i++) {
				if (strs[i] == NULL)
					return (-1);
				value_sz += strlen(strs[i]) + 1;
			}
		}
		break;
	case DATA_TYPE_HRTIME:
		value_sz = sizeof (hrtime_t);
		break;
	case DATA_TYPE_NVLIST:
		value_sz = NV_ALIGN(sizeof (nvlist_t));
		break;
	case DATA_TYPE_NVLIST_ARRAY:
		value_sz = (uint64_t)nelem * sizeof (uint64_t) +
		    (uint64_t)nelem * NV_ALIGN(sizeof (nvlist_t));
		break;
	default:
		return (-1);
	}

	return (value_sz > INT32_MAX ? -1 : (int)value_sz);
}