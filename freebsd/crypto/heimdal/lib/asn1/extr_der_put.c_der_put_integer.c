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
der_put_integer (unsigned char *p, size_t len, const int *v, size_t *size)
{
    unsigned char *base = p;
    int val = *v;

    if(val >= 0) {
	do {
	    if(len < 1)
		return ASN1_OVERFLOW;
	    *p-- = val % 256;
	    len--;
	    val /= 256;
	} while(val);
	if(p[1] >= 128) {
	    if(len < 1)
		return ASN1_OVERFLOW;
	    *p-- = 0;
	    len--;
	}
    } else {
	val = ~val;
	do {
	    if(len < 1)
		return ASN1_OVERFLOW;
	    *p-- = ~(val % 256);
	    len--;
	    val /= 256;
	} while(val);
	if(p[1] < 128) {
	    if(len < 1)
		return ASN1_OVERFLOW;
	    *p-- = 0xff;
	    len--;
	}
    }
    *size = base - p;
    return 0;
}