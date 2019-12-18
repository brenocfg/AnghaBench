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
 int /*<<< orphan*/  BHND_NV_LOG (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  BHND_NV_PANIC (char*,int) ; 
 size_t SIZE_MAX ; 
 int /*<<< orphan*/  bhnd_nvram_base_type (int) ; 
 int /*<<< orphan*/  bhnd_nvram_is_array_type (int) ; 
 int /*<<< orphan*/  bhnd_nvram_type_name (int /*<<< orphan*/ ) ; 
 size_t bhnd_nvram_type_width (int) ; 
 size_t strnlen (void const*,size_t) ; 

size_t
bhnd_nvram_value_size(const void *inp, size_t ilen, bhnd_nvram_type itype,
    size_t nelem)
{
	/* If nelem 0, nothing to do */
	if (nelem == 0)
		return (0);

	/* Non-array types must have an nelem value of 1 */
	if (!bhnd_nvram_is_array_type(itype) && nelem != 1)
		return (0);

	switch (itype) {
	case BHND_NVRAM_TYPE_UINT8_ARRAY:
	case BHND_NVRAM_TYPE_UINT16_ARRAY:
	case BHND_NVRAM_TYPE_UINT32_ARRAY:
	case BHND_NVRAM_TYPE_UINT64_ARRAY:
	case BHND_NVRAM_TYPE_INT8_ARRAY:
	case BHND_NVRAM_TYPE_INT16_ARRAY:
	case BHND_NVRAM_TYPE_INT32_ARRAY:
	case BHND_NVRAM_TYPE_INT64_ARRAY:
	case BHND_NVRAM_TYPE_CHAR_ARRAY:
	case BHND_NVRAM_TYPE_BOOL_ARRAY:{
		size_t width;

		width = bhnd_nvram_type_width(itype);

		/* Would nelem * width overflow? */
		if (SIZE_MAX / nelem < width) {
			BHND_NV_LOG("cannot represent size %s[%zu]\n",
			    bhnd_nvram_type_name(bhnd_nvram_base_type(itype)),
			    nelem);
			return (0);
		}

		return (nelem * width);
	}

	case BHND_NVRAM_TYPE_STRING_ARRAY: {
		const char	*p;
		size_t		 total_size;

		if (inp == NULL)
			return (0);

		/* Iterate over the NUL-terminated strings to calculate
		 * total byte length */
		p = inp;
		total_size = 0;
		for (size_t i = 0; i < nelem; i++) {
			size_t	elem_size;

			elem_size = strnlen(p, ilen - total_size);
			p += elem_size;

			/* Check for (and skip) terminating NUL */
			if (total_size < ilen && *p == '\0') {
				elem_size++;
				p++;
			}

			/* Would total_size + elem_size overflow?
			 * 
			 * A memory range larger than SIZE_MAX shouldn't be,
			 * possible, but include the check for completeness */
			if (SIZE_MAX - total_size < elem_size)
				return (0);

			total_size += elem_size;
		}

		return (total_size);
	}

	case BHND_NVRAM_TYPE_STRING: {
		size_t size;

		if (inp == NULL)
			return (0);

		/* Find length */
		size = strnlen(inp, ilen);

		/* Is there a terminating NUL, or did we just hit the
		 * end of the string input */
		if (size < ilen)
			size++;

		return (size);
	}

	case BHND_NVRAM_TYPE_NULL:
		return (0);

	case BHND_NVRAM_TYPE_DATA:
		if (inp == NULL)
			return (0);

		return (ilen);

	case BHND_NVRAM_TYPE_BOOL:
		return (sizeof(bhnd_nvram_bool_t));

	case BHND_NVRAM_TYPE_INT8:
	case BHND_NVRAM_TYPE_UINT8:
	case BHND_NVRAM_TYPE_CHAR:
		return (sizeof(uint8_t));

	case BHND_NVRAM_TYPE_INT16:
	case BHND_NVRAM_TYPE_UINT16:
		return (sizeof(uint16_t));

	case BHND_NVRAM_TYPE_INT32:
	case BHND_NVRAM_TYPE_UINT32:
		return (sizeof(uint32_t));

	case BHND_NVRAM_TYPE_UINT64:
	case BHND_NVRAM_TYPE_INT64:
		return (sizeof(uint64_t));
	}

	/* Quiesce gcc4.2 */
	BHND_NV_PANIC("bhnd nvram type %u unknown", itype);
}