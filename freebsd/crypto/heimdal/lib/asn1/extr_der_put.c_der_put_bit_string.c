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
struct TYPE_3__ {int length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ heim_bit_string ;

/* Variables and functions */
 int ASN1_OVERFLOW ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,size_t) ; 

int
der_put_bit_string (unsigned char *p, size_t len,
		    const heim_bit_string *data, size_t *size)
{
    size_t data_size = (data->length + 7) / 8;
    if (len < data_size + 1)
	return ASN1_OVERFLOW;
    p -= data_size + 1;

    memcpy (p+2, data->data, data_size);
    if (data->length && (data->length % 8) != 0)
	p[1] = 8 - (data->length % 8);
    else
	p[1] = 0;
    *size = data_size + 1;
    return 0;
}