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
typedef  int /*<<< orphan*/  bhnd_nvram_type ;

/* Variables and functions */
 int EFTYPE ; 
 scalar_t__ bhnd_nvram_is_int_type (int /*<<< orphan*/ ) ; 
 int bhnd_nvram_parse_int (void const*,size_t,int,size_t*,void*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_nvram_val_elem_type (int /*<<< orphan*/ *) ; 
 int bhnd_nvram_value_coerce (void const*,size_t,int /*<<< orphan*/ ,void*,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhnd_nvram_val_bcm_macaddr_string_encode_elem(bhnd_nvram_val *value,
    const void *inp, size_t ilen, void *outp, size_t *olen,
    bhnd_nvram_type otype)
{
	size_t	nparsed;
	int	error;

	/* If integer encoding is requested, explicitly parse our
	 * non-0x-prefixed as a base 16 integer value */
	if (bhnd_nvram_is_int_type(otype)) {
		error = bhnd_nvram_parse_int(inp, ilen, 16, &nparsed, outp,
		    olen, otype);
		if (error)
			return (error);

		if (nparsed != ilen)
			return (EFTYPE);

		return (0);
	}

	/* Otherwise, use standard encoding support */
	return (bhnd_nvram_value_coerce(inp, ilen,
	    bhnd_nvram_val_elem_type(value), outp, olen, otype));
}