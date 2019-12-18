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
 int /*<<< orphan*/  bhnd_nvram_ident_octet_string (void const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bhnd_nvram_val_bcm_string_fmt ; 

__attribute__((used)) static int
bhnd_nvram_val_bcm_macaddr_string_filter(const bhnd_nvram_val_fmt **fmt,
    const void *inp, size_t ilen, bhnd_nvram_type itype)
{
	switch (itype) {
	case BHND_NVRAM_TYPE_STRING:
		/* Use the standard Broadcom string format implementation if
		 * the input is not an octet string. */
		if (!bhnd_nvram_ident_octet_string(inp, ilen, NULL, NULL))
			*fmt = &bhnd_nvram_val_bcm_string_fmt;

		return (0);
	default:
		return (EFTYPE);
	}
}