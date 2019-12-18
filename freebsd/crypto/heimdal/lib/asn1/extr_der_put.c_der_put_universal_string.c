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
struct TYPE_3__ {size_t length; int* data; } ;
typedef  TYPE_1__ heim_universal_string ;

/* Variables and functions */
 int ASN1_OVERFLOW ; 

int
der_put_universal_string (unsigned char *p, size_t len,
			  const heim_universal_string *data, size_t *size)
{
    size_t i;
    if (len / 4 < data->length)
	return ASN1_OVERFLOW;
    p -= data->length * 4;
    for (i = 0; i < data->length; i++) {
	p[1] = (data->data[i] >> 24) & 0xff;
	p[2] = (data->data[i] >> 16) & 0xff;
	p[3] = (data->data[i] >> 8) & 0xff;
	p[4] = data->data[i] & 0xff;
	p += 4;
    }
    if (size) *size = data->length * 4;
    return 0;
}