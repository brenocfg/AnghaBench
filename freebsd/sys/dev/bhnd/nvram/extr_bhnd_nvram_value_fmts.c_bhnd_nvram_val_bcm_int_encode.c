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
 int bhnd_nvram_val_generic_encode (int /*<<< orphan*/ *,void*,size_t*,scalar_t__) ; 
 int bhnd_nvram_val_printf (int /*<<< orphan*/ *,char*,void*,size_t*,char*) ; 

__attribute__((used)) static int
bhnd_nvram_val_bcm_int_encode(bhnd_nvram_val *value, void *outp, size_t *olen,
    bhnd_nvram_type otype)
{
	/* If encoding to a string, format multiple elements (if any) with a
	 * comma delimiter. */
	if (otype == BHND_NVRAM_TYPE_STRING)
		return (bhnd_nvram_val_printf(value, "%[]s", outp, olen, ","));

	return (bhnd_nvram_val_generic_encode(value, outp, olen, otype));
}