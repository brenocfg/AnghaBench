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
typedef  int bhnd_nvram_type ;

/* Variables and functions */
#define  BHND_NVRAM_TYPE_BOOL 151 
#define  BHND_NVRAM_TYPE_BOOL_ARRAY 150 
#define  BHND_NVRAM_TYPE_CHAR 149 
#define  BHND_NVRAM_TYPE_CHAR_ARRAY 148 
#define  BHND_NVRAM_TYPE_DATA 147 
#define  BHND_NVRAM_TYPE_INT16 146 
#define  BHND_NVRAM_TYPE_INT16_ARRAY 145 
#define  BHND_NVRAM_TYPE_INT32 144 
#define  BHND_NVRAM_TYPE_INT32_ARRAY 143 
#define  BHND_NVRAM_TYPE_INT64 142 
#define  BHND_NVRAM_TYPE_INT64_ARRAY 141 
#define  BHND_NVRAM_TYPE_INT8 140 
#define  BHND_NVRAM_TYPE_INT8_ARRAY 139 
#define  BHND_NVRAM_TYPE_NULL 138 
#define  BHND_NVRAM_TYPE_STRING 137 
#define  BHND_NVRAM_TYPE_STRING_ARRAY 136 
#define  BHND_NVRAM_TYPE_UINT16 135 
#define  BHND_NVRAM_TYPE_UINT16_ARRAY 134 
#define  BHND_NVRAM_TYPE_UINT32 133 
#define  BHND_NVRAM_TYPE_UINT32_ARRAY 132 
#define  BHND_NVRAM_TYPE_UINT64 131 
#define  BHND_NVRAM_TYPE_UINT64_ARRAY 130 
#define  BHND_NVRAM_TYPE_UINT8 129 
#define  BHND_NVRAM_TYPE_UINT8_ARRAY 128 
 int /*<<< orphan*/  BHND_NV_PANIC (char*,int) ; 

const char *
bhnd_nvram_type_name(bhnd_nvram_type type)
{
	switch (type) {
	case BHND_NVRAM_TYPE_UINT8:
		return ("uint8");
	case BHND_NVRAM_TYPE_UINT16:
		return ("uint16");
	case BHND_NVRAM_TYPE_UINT32:
		return ("uint32");
	case BHND_NVRAM_TYPE_UINT64:
		return ("uint64");
	case BHND_NVRAM_TYPE_CHAR:
		return ("char");
	case BHND_NVRAM_TYPE_INT8:
		return ("int8");
	case BHND_NVRAM_TYPE_INT16:
		return ("int16");
	case BHND_NVRAM_TYPE_INT32:
		return ("int32");
	case BHND_NVRAM_TYPE_INT64:
		return ("int64");
	case BHND_NVRAM_TYPE_STRING:
		return ("string");
	case BHND_NVRAM_TYPE_BOOL:
		return ("bool");
	case BHND_NVRAM_TYPE_NULL:
		return ("null");
	case BHND_NVRAM_TYPE_DATA:
		return ("data");
	case BHND_NVRAM_TYPE_UINT8_ARRAY:
		return ("uint8[]");
	case BHND_NVRAM_TYPE_UINT16_ARRAY:
		return ("uint16[]");
	case BHND_NVRAM_TYPE_UINT32_ARRAY:
		return ("uint32[]");
	case BHND_NVRAM_TYPE_UINT64_ARRAY:
		return ("uint64[]");
	case BHND_NVRAM_TYPE_INT8_ARRAY:
		return ("int8[]");
	case BHND_NVRAM_TYPE_INT16_ARRAY:
		return ("int16[]");
	case BHND_NVRAM_TYPE_INT32_ARRAY:
		return ("int32[]");
	case BHND_NVRAM_TYPE_INT64_ARRAY:
		return ("int64[]");
	case BHND_NVRAM_TYPE_CHAR_ARRAY:
		return ("char[]");
	case BHND_NVRAM_TYPE_STRING_ARRAY:
		return ("string[]");
	case BHND_NVRAM_TYPE_BOOL_ARRAY:
		return ("bool[]");
	}

	/* Quiesce gcc4.2 */
	BHND_NV_PANIC("bhnd nvram type %u unknown", type);
}