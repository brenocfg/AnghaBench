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
typedef  int /*<<< orphan*/  len ;
struct TYPE_3__ {size_t length; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ heim_bit_string ;

/* Variables and functions */
 int ASN1_BAD_FORMAT ; 
 int ASN1_OVERRUN ; 
 int ENOMEM ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 

int
der_get_bit_string (const unsigned char *p, size_t len,
		    heim_bit_string *data, size_t *size)
{
    if (len < 1)
	return ASN1_OVERRUN;
    if (p[0] > 7)
	return ASN1_BAD_FORMAT;
    if (len - 1 == 0 && p[0] != 0)
	return ASN1_BAD_FORMAT;
    /* check if any of the three upper bits are set
     * any of them will cause a interger overrun */
    if ((len - 1) >> (sizeof(len) * 8 - 3))
	return ASN1_OVERRUN;
    data->length = (len - 1) * 8;
    data->data = malloc(len - 1);
    if (data->data == NULL && (len - 1) != 0)
	return ENOMEM;
    /* copy data is there is data to copy */
    if (len - 1 != 0) {
      memcpy (data->data, p + 1, len - 1);
      data->length -= p[0];
    }
    if(size) *size = len;
    return 0;
}