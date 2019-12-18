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
typedef  int /*<<< orphan*/  bhnd_nvram_val ;
typedef  scalar_t__ bhnd_nvram_type ;

/* Variables and functions */
 scalar_t__ BHND_NVRAM_TYPE_STRING ; 
 int /*<<< orphan*/  BHND_NV_ASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bhnd_nvram_is_int_type (scalar_t__) ; 
 scalar_t__ bhnd_nvram_is_signed_type (scalar_t__) ; 
 scalar_t__ bhnd_nvram_val_elem_type (int /*<<< orphan*/ *) ; 
 int bhnd_nvram_val_generic_encode_elem (int /*<<< orphan*/ *,void const*,size_t,void*,size_t*,scalar_t__) ; 
 int bhnd_nvram_value_printf (char const*,void const*,size_t,scalar_t__,void*,size_t*) ; 

__attribute__((used)) static int
bhnd_nvram_val_bcm_decimal_encode_elem(bhnd_nvram_val *value, const void *inp,
    size_t ilen, void *outp, size_t *olen, bhnd_nvram_type otype)
{
	const char	*sfmt;
	bhnd_nvram_type	 itype;

	itype = bhnd_nvram_val_elem_type(value);
	BHND_NV_ASSERT(bhnd_nvram_is_int_type(itype), ("invalid type"));

	/* If not encoding as a string, perform generic value encoding */
	if (otype != BHND_NVRAM_TYPE_STRING)
		return (bhnd_nvram_val_generic_encode_elem(value, inp, ilen,
		    outp, olen, otype));

	sfmt = bhnd_nvram_is_signed_type(itype) ? "%I64d" : "%I64u";
	return (bhnd_nvram_value_printf(sfmt, inp, ilen, itype, outp, olen));
}