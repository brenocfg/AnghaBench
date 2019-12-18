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
typedef  int /*<<< orphan*/  bhnd_nvram_val_fmt ;
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
 int /*<<< orphan*/  const bhnd_nvram_val_bool_array_fmt ; 
 int /*<<< orphan*/  const bhnd_nvram_val_bool_fmt ; 
 int /*<<< orphan*/  const bhnd_nvram_val_char_array_fmt ; 
 int /*<<< orphan*/  const bhnd_nvram_val_char_fmt ; 
 int /*<<< orphan*/  const bhnd_nvram_val_data_fmt ; 
 int /*<<< orphan*/  const bhnd_nvram_val_int16_array_fmt ; 
 int /*<<< orphan*/  const bhnd_nvram_val_int16_fmt ; 
 int /*<<< orphan*/  const bhnd_nvram_val_int32_array_fmt ; 
 int /*<<< orphan*/  const bhnd_nvram_val_int32_fmt ; 
 int /*<<< orphan*/  const bhnd_nvram_val_int64_array_fmt ; 
 int /*<<< orphan*/  const bhnd_nvram_val_int64_fmt ; 
 int /*<<< orphan*/  const bhnd_nvram_val_int8_array_fmt ; 
 int /*<<< orphan*/  const bhnd_nvram_val_int8_fmt ; 
 int /*<<< orphan*/  const bhnd_nvram_val_null_fmt ; 
 int /*<<< orphan*/  const bhnd_nvram_val_string_array_fmt ; 
 int /*<<< orphan*/  const bhnd_nvram_val_string_fmt ; 
 int /*<<< orphan*/  const bhnd_nvram_val_uint16_array_fmt ; 
 int /*<<< orphan*/  const bhnd_nvram_val_uint16_fmt ; 
 int /*<<< orphan*/  const bhnd_nvram_val_uint32_array_fmt ; 
 int /*<<< orphan*/  const bhnd_nvram_val_uint32_fmt ; 
 int /*<<< orphan*/  const bhnd_nvram_val_uint64_array_fmt ; 
 int /*<<< orphan*/  const bhnd_nvram_val_uint64_fmt ; 
 int /*<<< orphan*/  const bhnd_nvram_val_uint8_array_fmt ; 
 int /*<<< orphan*/  const bhnd_nvram_val_uint8_fmt ; 

const bhnd_nvram_val_fmt *
bhnd_nvram_val_default_fmt(bhnd_nvram_type type)
{
	switch (type) {
	case BHND_NVRAM_TYPE_UINT8:
		return (&bhnd_nvram_val_uint8_fmt);
	case BHND_NVRAM_TYPE_UINT16:
		return (&bhnd_nvram_val_uint16_fmt);
	case BHND_NVRAM_TYPE_UINT32:
		return (&bhnd_nvram_val_uint32_fmt);
	case BHND_NVRAM_TYPE_UINT64:
		return (&bhnd_nvram_val_uint64_fmt);
	case BHND_NVRAM_TYPE_INT8:
		return (&bhnd_nvram_val_int8_fmt);
	case BHND_NVRAM_TYPE_INT16:
		return (&bhnd_nvram_val_int16_fmt);
	case BHND_NVRAM_TYPE_INT32:
		return (&bhnd_nvram_val_int32_fmt);
	case BHND_NVRAM_TYPE_INT64:
		return (&bhnd_nvram_val_int64_fmt);
	case BHND_NVRAM_TYPE_CHAR:
		return (&bhnd_nvram_val_char_fmt);
	case BHND_NVRAM_TYPE_STRING:
		return (&bhnd_nvram_val_string_fmt);
	case BHND_NVRAM_TYPE_BOOL:
		return (&bhnd_nvram_val_bool_fmt);
	case BHND_NVRAM_TYPE_NULL:
		return (&bhnd_nvram_val_null_fmt);
	case BHND_NVRAM_TYPE_DATA:
		return (&bhnd_nvram_val_data_fmt);
	case BHND_NVRAM_TYPE_UINT8_ARRAY:
		return (&bhnd_nvram_val_uint8_array_fmt);
	case BHND_NVRAM_TYPE_UINT16_ARRAY:
		return (&bhnd_nvram_val_uint16_array_fmt);
	case BHND_NVRAM_TYPE_UINT32_ARRAY:
		return (&bhnd_nvram_val_uint32_array_fmt);
	case BHND_NVRAM_TYPE_UINT64_ARRAY:
		return (&bhnd_nvram_val_uint64_array_fmt);
	case BHND_NVRAM_TYPE_INT8_ARRAY:
		return (&bhnd_nvram_val_int8_array_fmt);
	case BHND_NVRAM_TYPE_INT16_ARRAY:
		return (&bhnd_nvram_val_int16_array_fmt);
	case BHND_NVRAM_TYPE_INT32_ARRAY:
		return (&bhnd_nvram_val_int32_array_fmt);
	case BHND_NVRAM_TYPE_INT64_ARRAY:
		return (&bhnd_nvram_val_int64_array_fmt);
	case BHND_NVRAM_TYPE_CHAR_ARRAY:
		return (&bhnd_nvram_val_char_array_fmt);
	case BHND_NVRAM_TYPE_STRING_ARRAY:
		return (&bhnd_nvram_val_string_array_fmt);
	case BHND_NVRAM_TYPE_BOOL_ARRAY:
		return (&bhnd_nvram_val_bool_array_fmt);
	}
	
	/* Quiesce gcc4.2 */
	BHND_NV_PANIC("bhnd nvram type %u unknown", type);
}