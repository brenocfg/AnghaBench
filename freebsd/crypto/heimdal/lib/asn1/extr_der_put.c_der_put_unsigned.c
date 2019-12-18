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

/* Variables and functions */
 int ASN1_OVERFLOW ; 

int
der_put_unsigned (unsigned char *p, size_t len, const unsigned *v, size_t *size)
{
    unsigned char *base = p;
    unsigned val = *v;

    if (val) {
	while (len > 0 && val) {
	    *p-- = val % 256;
	    val /= 256;
	    --len;
	}
	if (val != 0)
	    return ASN1_OVERFLOW;
	else {
	    if(p[1] >= 128) {
		if(len < 1)
		    return ASN1_OVERFLOW;
		*p-- = 0;
	    }
	    *size = base - p;
	    return 0;
	}
    } else if (len < 1)
	return ASN1_OVERFLOW;
    else {
	*p    = 0;
	*size = 1;
	return 0;
    }
}