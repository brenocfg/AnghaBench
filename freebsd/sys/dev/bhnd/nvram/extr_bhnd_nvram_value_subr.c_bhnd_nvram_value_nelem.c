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
 int /*<<< orphan*/  BHND_NV_ASSERT (int,char*) ; 
 int /*<<< orphan*/  BHND_NV_PANIC (char*,int) ; 
 int EFAULT ; 
 int EFTYPE ; 
 size_t bhnd_nvram_type_width (int) ; 
 int bhnd_nvram_value_check_aligned (void const*,size_t,int) ; 
 size_t strnlen (char const*,size_t) ; 

int
bhnd_nvram_value_nelem(const void *inp, size_t ilen, bhnd_nvram_type itype,
    size_t *nelem)
{
	int	error;

	BHND_NV_ASSERT(inp != NULL, ("NULL inp"));

	/* Check alignment */
	if ((error = bhnd_nvram_value_check_aligned(inp, ilen, itype)))
		return (error);

	switch (itype) {
	case BHND_NVRAM_TYPE_DATA:
		/* Always exactly one element */
		*nelem = 1;
		return (0);

	case BHND_NVRAM_TYPE_NULL:
		/* Must be zero length */
		if (ilen != 0)
			return (EFAULT);

		/* Always exactly one element */
		*nelem = 1;
		return (0);

	case BHND_NVRAM_TYPE_STRING:
		/* Always exactly one element */
		*nelem = 1;
		return (0);

	case BHND_NVRAM_TYPE_STRING_ARRAY: {
		const char	*p;
		size_t		 nleft;

		/* Iterate over the NUL-terminated strings to calculate
		 * total element count */
		p = inp;
		nleft = ilen;
		*nelem = 0;
		while (nleft > 0) {
			size_t slen;

			/* Increment element count */
			(*nelem)++;

			/* Determine string length */
			slen = strnlen(p, nleft);
			nleft -= slen;
	
			/* Advance input */
			p += slen;

			/* Account for trailing NUL, if we haven't hit the end
			 * of the input */
			if (nleft > 0) {
				nleft--;
				p++;
			}
		}

		return (0);
	}

	case BHND_NVRAM_TYPE_UINT8_ARRAY:
	case BHND_NVRAM_TYPE_UINT16_ARRAY:
	case BHND_NVRAM_TYPE_UINT32_ARRAY:
	case BHND_NVRAM_TYPE_UINT64_ARRAY:
	case BHND_NVRAM_TYPE_INT8_ARRAY:
	case BHND_NVRAM_TYPE_INT16_ARRAY:
	case BHND_NVRAM_TYPE_INT32_ARRAY:
	case BHND_NVRAM_TYPE_INT64_ARRAY:
	case BHND_NVRAM_TYPE_CHAR_ARRAY:
	case BHND_NVRAM_TYPE_BOOL_ARRAY: {
		size_t width = bhnd_nvram_type_width(itype);
		BHND_NV_ASSERT(width != 0, ("invalid width"));

		*nelem = ilen / width;
		return (0);
	}

	case BHND_NVRAM_TYPE_INT8:
	case BHND_NVRAM_TYPE_UINT8:
	case BHND_NVRAM_TYPE_CHAR:
	case BHND_NVRAM_TYPE_INT16:
	case BHND_NVRAM_TYPE_UINT16:
	case BHND_NVRAM_TYPE_INT32:
	case BHND_NVRAM_TYPE_UINT32:
	case BHND_NVRAM_TYPE_INT64:
	case BHND_NVRAM_TYPE_UINT64:
	case BHND_NVRAM_TYPE_BOOL:
		/* Length must be equal to the size of exactly one
		 * element (arrays can represent zero elements -- non-array
		 * types cannot) */
		if (ilen != bhnd_nvram_type_width(itype))
			return (EFTYPE);
		*nelem = 1;
		return (0);
	}

	/* Quiesce gcc4.2 */
	BHND_NV_PANIC("bhnd nvram type %u unknown", itype);
}