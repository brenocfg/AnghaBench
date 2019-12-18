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

/* Variables and functions */
 int ASN1_OVERRUN ; 

int
der_get_integer (const unsigned char *p, size_t len,
		 int *ret, size_t *size)
{
    int val = 0;
    size_t oldlen = len;

    if (len > sizeof(int))
	return ASN1_OVERRUN;

    if (len > 0) {
	val = (signed char)*p++;
	while (--len)
	    val = val * 256 + *p++;
    }
    *ret = val;
    if(size) *size = oldlen;
    return 0;
}