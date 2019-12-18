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
struct TYPE_3__ {size_t length; unsigned char* data; } ;
typedef  TYPE_1__ heim_universal_string ;

/* Variables and functions */
 int ASN1_BAD_CHARACTER ; 
 int ASN1_BAD_FORMAT ; 
 int ENOMEM ; 
 int ERANGE ; 
 int UINT_MAX ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 unsigned char* malloc (int) ; 

int
der_get_universal_string (const unsigned char *p, size_t len,
			  heim_universal_string *data, size_t *size)
{
    size_t i;

    if (len & 3)
	return ASN1_BAD_FORMAT;
    data->length = len / 4;
    if (data->length > UINT_MAX/sizeof(data->data[0]))
	return ERANGE;
    data->data = malloc(data->length * sizeof(data->data[0]));
    if (data->data == NULL && data->length != 0)
	return ENOMEM;

    for (i = 0; i < data->length; i++) {
	data->data[i] = (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
	p += 4;
	/* check for NUL in the middle of the string */
	if (data->data[i] == 0 && i != (data->length - 1)) {
	    free(data->data);
	    data->data = NULL;
	    data->length = 0;
	    return ASN1_BAD_CHARACTER;
	}
    }
    if (size) *size = len;
    return 0;
}