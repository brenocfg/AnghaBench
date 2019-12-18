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
 scalar_t__ BHND_NVRAM_TYPE_STRING ; 
 scalar_t__ bhnd_nvram_base_type (int /*<<< orphan*/ ) ; 
 void* bhnd_nvram_val_bytes (int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *) ; 
 int bhnd_nvram_val_printf (int /*<<< orphan*/ *,char*,void*,size_t*,char*) ; 
 int bhnd_nvram_value_coerce (void const*,size_t,int /*<<< orphan*/ ,void*,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhnd_nvram_val_bcm_macaddr_encode(bhnd_nvram_val *value, void *outp,
    size_t *olen, bhnd_nvram_type otype)
{
	const void	*inp;
	bhnd_nvram_type	 itype;
	size_t		 ilen;

	/*
	 * If converting to a string (or a single-element string array),
	 * produce an octet string (00:00:...).
	 */
	if (bhnd_nvram_base_type(otype) == BHND_NVRAM_TYPE_STRING) {
		return (bhnd_nvram_val_printf(value, "%[]02hhX", outp, olen,
		    ":"));
	}

	/* Otherwise, use standard encoding support */
	inp = bhnd_nvram_val_bytes(value, &ilen, &itype);
	return (bhnd_nvram_value_coerce(inp, ilen, itype, outp, olen, otype));}