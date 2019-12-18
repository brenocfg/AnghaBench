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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int bhnd_nvram_type ;
typedef  int /*<<< orphan*/  bhnd_nvram_bool_t ;

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

size_t
bhnd_nvram_type_width(bhnd_nvram_type type)
{
	switch (type) {
	case BHND_NVRAM_TYPE_STRING:
	case BHND_NVRAM_TYPE_STRING_ARRAY:
	case BHND_NVRAM_TYPE_DATA:
		return (0);

	case BHND_NVRAM_TYPE_NULL:
		return (0);

	case BHND_NVRAM_TYPE_BOOL:
	case BHND_NVRAM_TYPE_BOOL_ARRAY:
		return (sizeof(bhnd_nvram_bool_t));

	case BHND_NVRAM_TYPE_CHAR:
	case BHND_NVRAM_TYPE_CHAR_ARRAY:
	case BHND_NVRAM_TYPE_UINT8:
	case BHND_NVRAM_TYPE_UINT8_ARRAY:
	case BHND_NVRAM_TYPE_INT8:
	case BHND_NVRAM_TYPE_INT8_ARRAY:
		return (sizeof(uint8_t));

	case BHND_NVRAM_TYPE_UINT16:
	case BHND_NVRAM_TYPE_UINT16_ARRAY:
	case BHND_NVRAM_TYPE_INT16:
	case BHND_NVRAM_TYPE_INT16_ARRAY:
		return (sizeof(uint16_t));

	case BHND_NVRAM_TYPE_UINT32:
	case BHND_NVRAM_TYPE_UINT32_ARRAY:
	case BHND_NVRAM_TYPE_INT32:
	case BHND_NVRAM_TYPE_INT32_ARRAY:
		return (sizeof(uint32_t));

	case BHND_NVRAM_TYPE_UINT64:
	case BHND_NVRAM_TYPE_UINT64_ARRAY:
	case BHND_NVRAM_TYPE_INT64:
	case BHND_NVRAM_TYPE_INT64_ARRAY:
		return (sizeof(uint64_t));
	}

	/* Quiesce gcc4.2 */
	BHND_NV_PANIC("bhnd nvram type %u unknown", type);
}