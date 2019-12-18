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
struct TYPE_3__ {size_t length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ heim_octet_string ;

/* Variables and functions */
 int ASN1_OVERFLOW ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,size_t) ; 

int
der_put_octet_string (unsigned char *p, size_t len,
		      const heim_octet_string *data, size_t *size)
{
    if (len < data->length)
	return ASN1_OVERFLOW;
    p -= data->length;
    memcpy (p+1, data->data, data->length);
    *size = data->length;
    return 0;
}