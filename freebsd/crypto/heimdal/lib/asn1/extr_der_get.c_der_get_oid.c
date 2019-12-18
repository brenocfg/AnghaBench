#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned char* components; size_t length; } ;
typedef  TYPE_1__ heim_oid ;

/* Variables and functions */
 int ASN1_BAD_LENGTH ; 
 int ASN1_OVERRUN ; 
 int ENOMEM ; 
 int ERANGE ; 
 int UINT_MAX ; 
 int /*<<< orphan*/  der_free_oid (TYPE_1__*) ; 
 unsigned char* malloc (size_t) ; 

int
der_get_oid (const unsigned char *p, size_t len,
	     heim_oid *data, size_t *size)
{
    size_t n;
    size_t oldlen = len;

    if (len < 1)
	return ASN1_OVERRUN;

    if (len > len + 1)
	return ASN1_BAD_LENGTH;

    if (len + 1 > UINT_MAX/sizeof(data->components[0]))
	return ERANGE;

    data->components = malloc((len + 1) * sizeof(data->components[0]));
    if (data->components == NULL)
	return ENOMEM;
    data->components[0] = (*p) / 40;
    data->components[1] = (*p) % 40;
    --len;
    ++p;
    for (n = 2; len > 0; ++n) {
	unsigned u = 0, u1;

	do {
	    --len;
	    u1 = u * 128 + (*p++ % 128);
	    /* check that we don't overflow the element */
	    if (u1 < u) {
		der_free_oid(data);
		return ASN1_OVERRUN;
	    }
	    u = u1;
	} while (len > 0 && p[-1] & 0x80);
	data->components[n] = u;
    }
    if (n > 2 && p[-1] & 0x80) {
	der_free_oid (data);
	return ASN1_OVERRUN;
    }
    data->length = n;
    if (size)
	*size = oldlen;
    return 0;
}