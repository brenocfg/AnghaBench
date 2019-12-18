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
typedef  int /*<<< orphan*/  Der_type ;
typedef  int /*<<< orphan*/  Der_class ;

/* Variables and functions */
 int ASN1_OVERFLOW ; 
 void* MAKE_TAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
der_put_tag (unsigned char *p, size_t len, Der_class class, Der_type type,
	     unsigned int tag, size_t *size)
{
    if (tag <= 30) {
	if (len < 1)
	    return ASN1_OVERFLOW;
	*p = MAKE_TAG(class, type, tag);
	*size = 1;
    } else {
	size_t ret = 0;
	unsigned int continuation = 0;

	do {
	    if (len < 1)
		return ASN1_OVERFLOW;
	    *p-- = tag % 128 | continuation;
	    len--;
	    ret++;
	    tag /= 128;
	    continuation = 0x80;
	} while(tag > 0);
	if (len < 1)
	    return ASN1_OVERFLOW;
	*p-- = MAKE_TAG(class, type, 0x1f);
	ret++;
	*size = ret;
    }
    return 0;
}