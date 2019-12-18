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
typedef  scalar_t__ Der_type ;
typedef  scalar_t__ Der_class ;

/* Variables and functions */
 int ASN1_OVERFLOW ; 
 int ASN1_OVERRUN ; 

int
der_get_tag (const unsigned char *p, size_t len,
	     Der_class *class, Der_type *type,
	     unsigned int *tag, size_t *size)
{
    size_t ret = 0;
    if (len < 1)
	return ASN1_OVERRUN;
    *class = (Der_class)(((*p) >> 6) & 0x03);
    *type = (Der_type)(((*p) >> 5) & 0x01);
    *tag = (*p) & 0x1f;
    p++; len--; ret++;
    if(*tag == 0x1f) {
	unsigned int continuation;
	unsigned int tag1;
	*tag = 0;
	do {
	    if(len < 1)
		return ASN1_OVERRUN;
	    continuation = *p & 128;
	    tag1 = *tag * 128 + (*p % 128);
	    /* check that we don't overflow the tag */
	    if (tag1 < *tag)
		return ASN1_OVERFLOW;
	    *tag = tag1;
	    p++; len--; ret++;
	} while(continuation);
    }
    if(size) *size = ret;
    return 0;
}