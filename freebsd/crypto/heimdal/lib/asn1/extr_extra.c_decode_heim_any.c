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
struct TYPE_4__ {size_t length; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ heim_any ;
typedef  int /*<<< orphan*/  Der_type ;
typedef  int /*<<< orphan*/  Der_class ;

/* Variables and functions */
 size_t ASN1_INDEFINITE ; 
 int ASN1_OVERFLOW ; 
 int ENOMEM ; 
 int der_get_length (unsigned char const*,size_t,size_t*,size_t*) ; 
 int der_get_tag (unsigned char const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*,size_t*) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int
decode_heim_any(const unsigned char *p, size_t len,
		heim_any *data, size_t *size)
{
    size_t len_len, length, l;
    Der_class thisclass;
    Der_type thistype;
    unsigned int thistag;
    int e;

    memset(data, 0, sizeof(*data));

    e = der_get_tag (p, len, &thisclass, &thistype, &thistag, &l);
    if (e) return e;
    if (l > len)
	return ASN1_OVERFLOW;
    e = der_get_length(p + l, len - l, &length, &len_len);
    if (e) return e;
    if (length == ASN1_INDEFINITE) {
        if (len < len_len + l)
	    return ASN1_OVERFLOW;
	length = len - (len_len + l);
    } else {
	if (len < length + len_len + l)
	    return ASN1_OVERFLOW;
    }

    data->data = malloc(length + len_len + l);
    if (data->data == NULL)
	return ENOMEM;
    data->length = length + len_len + l;
    memcpy(data->data, p, length + len_len + l);

    if (size)
	*size = length + len_len + l;

    return 0;
}