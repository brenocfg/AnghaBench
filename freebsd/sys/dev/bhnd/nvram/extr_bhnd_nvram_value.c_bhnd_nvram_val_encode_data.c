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
typedef  scalar_t__ bhnd_nvram_type ;

/* Variables and functions */
 scalar_t__ BHND_NVRAM_TYPE_DATA ; 
#define  BHND_NVRAM_TYPE_STRING 129 
#define  BHND_NVRAM_TYPE_STRING_ARRAY 128 
 int /*<<< orphan*/  BHND_NVRAM_TYPE_UINT8_ARRAY ; 
 int /*<<< orphan*/  BHND_NV_ASSERT (int,char*) ; 
 int bhnd_nvram_value_coerce (void const*,size_t,int /*<<< orphan*/ ,void*,size_t*,scalar_t__) ; 
 int bhnd_nvram_value_printf (char*,void const*,size_t,int /*<<< orphan*/ ,void*,size_t*,char*) ; 

__attribute__((used)) static int
bhnd_nvram_val_encode_data(const void *inp, size_t ilen, bhnd_nvram_type itype,
    void *outp, size_t *olen, bhnd_nvram_type otype)
{
	BHND_NV_ASSERT(itype == BHND_NVRAM_TYPE_DATA,
	    ("unsupported type: %d", itype));

	/* Write to output */
	switch (otype) {
	case BHND_NVRAM_TYPE_STRING:
	case BHND_NVRAM_TYPE_STRING_ARRAY:
		/* If encoding as a string, produce an EFI-style hexadecimal
		 * byte array (HF1F...) by interpreting the octet string
		 * as an array of uint8 values */
		return (bhnd_nvram_value_printf("H%[]02hhX", inp, ilen,
		    BHND_NVRAM_TYPE_UINT8_ARRAY, outp, olen, ""));

	default:
		/* Fall back on direct interpretation as an array of 8-bit
		 * integers array */
		return (bhnd_nvram_value_coerce(inp, ilen,
		    BHND_NVRAM_TYPE_UINT8_ARRAY, outp, olen, otype));
	}
}