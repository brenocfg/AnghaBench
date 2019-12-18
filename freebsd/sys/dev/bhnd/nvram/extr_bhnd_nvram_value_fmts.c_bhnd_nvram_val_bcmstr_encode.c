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
typedef  int /*<<< orphan*/  bhnd_nvram_val ;
typedef  int /*<<< orphan*/  bhnd_nvram_type ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NVRAM_TYPE_CHAR_ARRAY ; 
 int /*<<< orphan*/  BHND_NVRAM_VAL_BORROW_DATA ; 
 int /*<<< orphan*/  BHND_NV_LOG (char*,int) ; 
 scalar_t__ bhnd_nvram_ident_octet_string (void const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bhnd_nvram_is_array_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_nvram_val_bcm_macaddr_string_fmt ; 
 int /*<<< orphan*/  bhnd_nvram_val_bcm_string_csv_fmt ; 
 void* bhnd_nvram_val_bytes (int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *) ; 
 int bhnd_nvram_val_encode (int /*<<< orphan*/ *,void*,size_t*,int /*<<< orphan*/ ) ; 
 int bhnd_nvram_val_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,void const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_nvram_val_release (int /*<<< orphan*/ *) ; 
 int bhnd_nvram_value_coerce (void const*,size_t,int /*<<< orphan*/ ,void*,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhnd_nvram_val_bcmstr_encode(bhnd_nvram_val *value, void *outp, size_t *olen,
    bhnd_nvram_type otype)
{
	bhnd_nvram_val			 array;
	const bhnd_nvram_val_fmt	*array_fmt;
	const void			*inp;
	bhnd_nvram_type			itype;
	size_t				ilen;
	int				error;

	inp = bhnd_nvram_val_bytes(value, &ilen, &itype);

	/* If the output is not an array type (or if it's a character array),
	 * we can fall back on standard string encoding */
	if (!bhnd_nvram_is_array_type(otype) ||
	    otype == BHND_NVRAM_TYPE_CHAR_ARRAY)
	{
		return (bhnd_nvram_value_coerce(inp, ilen, itype, outp, olen,
		    otype));
	}

	/* Otherwise, we need to interpret our value as either a macaddr
	 * string, or a comma-delimited string. */
	inp = bhnd_nvram_val_bytes(value, &ilen, &itype);
	if (bhnd_nvram_ident_octet_string(inp, ilen, NULL, NULL))
		array_fmt = &bhnd_nvram_val_bcm_macaddr_string_fmt;
	else
		array_fmt = &bhnd_nvram_val_bcm_string_csv_fmt;

	/* Wrap in array-typed representation */
	error = bhnd_nvram_val_init(&array, array_fmt, inp, ilen, itype,
	    BHND_NVRAM_VAL_BORROW_DATA);
	if (error) {
		BHND_NV_LOG("error initializing array representation: %d\n",
		    error);
		return (error);
	}

	/* Ask the array-typed value to perform the encode */
	error = bhnd_nvram_val_encode(&array, outp, olen, otype);
	if (error)
		BHND_NV_LOG("error encoding array representation: %d\n", error);

	bhnd_nvram_val_release(&array);

	return (error);
}