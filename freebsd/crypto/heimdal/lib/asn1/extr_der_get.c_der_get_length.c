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
 size_t ASN1_INDEFINITE ; 
 int ASN1_OVERRUN ; 
 int der_get_unsigned (unsigned char const*,size_t,unsigned int*,size_t*) ; 

int
der_get_length (const unsigned char *p, size_t len,
		size_t *val, size_t *size)
{
    size_t v;

    if (len <= 0)
	return ASN1_OVERRUN;
    --len;
    v = *p++;
    if (v < 128) {
	*val = v;
	if(size) *size = 1;
    } else {
	int e;
	size_t l;
	unsigned tmp;

	if(v == 0x80){
	    *val = ASN1_INDEFINITE;
	    if(size) *size = 1;
	    return 0;
	}
	v &= 0x7F;
	if (len < v)
	    return ASN1_OVERRUN;
	e = der_get_unsigned (p, v, &tmp, &l);
	if(e) return e;
	*val = tmp;
	if(size) *size = l + 1;
    }
    return 0;
}