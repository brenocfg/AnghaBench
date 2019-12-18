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
typedef  int /*<<< orphan*/  in ;
typedef  unsigned char bom ;

/* Variables and functions */
 int WIND_ERR_LENGTH_NOT_MOD2 ; 
 int WIND_ERR_OVERRUN ; 
 unsigned int WIND_RW_BOM ; 
 unsigned int WIND_RW_LE ; 

int
wind_ucs2write(const uint16_t *in, size_t in_len, unsigned int *flags,
	       void *ptr, size_t *out_len)
{
    unsigned char *p = ptr;
    size_t len = *out_len;

    /** If in buffer is not of length be mod 2, WIND_ERR_LENGTH_NOT_MOD2 is returned*/
    if (len & 1)
	return WIND_ERR_LENGTH_NOT_MOD2;

    /** On zero input length, flags are preserved */
    if (in_len == 0) {
	*out_len = 0;
	return 0;
    }
    /** If flags have WIND_RW_BOM set, the byte order mark is written
     * first to the output data */
    if ((*flags) & WIND_RW_BOM) {
	uint16_t bom = 0xfffe;

	if (len < 2)
	    return WIND_ERR_OVERRUN;

	if ((*flags) & WIND_RW_LE) {
	    p[0] = (bom     ) & 0xff;
	    p[1] = (bom >> 8) & 0xff;
	} else {
	    p[1] = (bom     ) & 0xff;
	    p[0] = (bom >> 8) & 0xff;
	}
	len -= 2;
    }

    while (in_len) {
	/** If the output wont fit into out_len, WIND_ERR_OVERRUN is returned */
	if (len < 2)
	    return WIND_ERR_OVERRUN;
	if ((*flags) & WIND_RW_LE) {
	    p[0] = (in[0]     ) & 0xff;
	    p[1] = (in[0] >> 8) & 0xff;
	} else {
	    p[1] = (in[0]     ) & 0xff;
	    p[0] = (in[0] >> 8) & 0xff;
	}
	len -= 2;
	in_len--;
	p += 2;
	in++;
    }
    *out_len -= len;
    return 0;
}