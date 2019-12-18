#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned char* data; size_t length; scalar_t__ negative; } ;
typedef  TYPE_1__ heim_integer ;

/* Variables and functions */
 int ASN1_OVERFLOW ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 

int
der_put_heim_integer (unsigned char *p, size_t len,
		     const heim_integer *data, size_t *size)
{
    unsigned char *buf = data->data;
    int hibitset = 0;

    if (data->length == 0) {
	if (len < 1)
	    return ASN1_OVERFLOW;
	*p-- = 0;
	if (size)
	    *size = 1;
	return 0;
    }
    if (len < data->length)
	return ASN1_OVERFLOW;

    len -= data->length;

    if (data->negative) {
	int i, carry;
	for (i = data->length - 1, carry = 1; i >= 0; i--) {
	    *p = buf[i] ^ 0xff;
	    if (carry)
		carry = !++*p;
	    p--;
	}
	if (p[1] < 128) {
	    if (len < 1)
		return ASN1_OVERFLOW;
	    *p-- = 0xff;
	    len--;
	    hibitset = 1;
	}
    } else {
	p -= data->length;
	memcpy(p + 1, buf, data->length);

	if (p[1] >= 128) {
	    if (len < 1)
		return ASN1_OVERFLOW;
	    p[0] = 0;
	    len--;
	    hibitset = 1;
	}
    }
    if (size)
	*size = data->length + hibitset;
    return 0;
}