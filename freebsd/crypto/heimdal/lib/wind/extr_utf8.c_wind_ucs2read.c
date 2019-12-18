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
typedef  int uint16_t ;

/* Variables and functions */
 int WIND_ERR_LENGTH_NOT_MOD2 ; 
 int WIND_ERR_NO_BOM ; 
 int WIND_ERR_OVERRUN ; 
 unsigned int WIND_RW_BE ; 
 unsigned int WIND_RW_BOM ; 
 unsigned int WIND_RW_LE ; 

int
wind_ucs2read(const void *ptr, size_t len, unsigned int *flags,
	      uint16_t *out, size_t *out_len)
{
    const unsigned char *p = ptr;
    int little = ((*flags) & WIND_RW_LE);
    size_t olen = *out_len;

    /** if len is zero, flags are unchanged */
    if (len == 0) {
	*out_len = 0;
	return 0;
    }

    /** if len is odd, WIND_ERR_LENGTH_NOT_MOD2 is returned */
    if (len & 1)
	return WIND_ERR_LENGTH_NOT_MOD2;

    /**
     * If the flags WIND_RW_BOM is set, check for BOM. If not BOM is
     * found, check is LE/BE flag is already and use that otherwise
     * fail with WIND_ERR_NO_BOM. When done, clear WIND_RW_BOM and
     * the LE/BE flag and set the resulting LE/BE flag.
     */
    if ((*flags) & WIND_RW_BOM) {
	uint16_t bom = (p[0] << 8) + p[1];
	if (bom == 0xfffe || bom == 0xfeff) {
	    little = (bom == 0xfffe);
	    p += 2;
	    len -= 2;
	} else if (((*flags) & (WIND_RW_LE|WIND_RW_BE)) != 0) {
	    /* little already set */
	} else
	    return WIND_ERR_NO_BOM;
	*flags = ((*flags) & ~(WIND_RW_BOM|WIND_RW_LE|WIND_RW_BE));
	*flags |= little ? WIND_RW_LE : WIND_RW_BE;
    }

    while (len) {
	if (olen < 1)
	    return WIND_ERR_OVERRUN;
	if (little)
	    *out = (p[1] << 8) + p[0];
	else
	    *out = (p[0] << 8) + p[1];
	out++; p += 2; len -= 2; olen--;
    }
    *out_len -= olen;
    return 0;
}