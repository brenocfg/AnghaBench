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
#define  BHND_NVRAM_TYPE_STRING 128 
 int EFTYPE ; 
 int bhnd_nvram_base_type (int) ; 
 int /*<<< orphan*/  bhnd_nvram_is_int_type (int) ; 
 int /*<<< orphan*/  bhnd_nvram_val_bcm_string_fmt ; 

__attribute__((used)) static int
bhnd_nvram_val_bcm_int_filter(const bhnd_nvram_val_fmt **fmt, const void *inp,
    size_t ilen, bhnd_nvram_type itype)
{
	bhnd_nvram_type	itype_base;

	itype_base = bhnd_nvram_base_type(itype);

	switch (itype_base) {
	case BHND_NVRAM_TYPE_STRING:
		/*
		 * If the input is a string, delegate to the Broadcom
		 * string format -- preserving the original string value
		 * takes priority over enforcing hexadecimal/integer string
		 * formatting.
		 */
		*fmt = &bhnd_nvram_val_bcm_string_fmt;
		return (0);

	default:
		if (bhnd_nvram_is_int_type(itype_base))
			return (0);

		return (EFTYPE);
	}
}