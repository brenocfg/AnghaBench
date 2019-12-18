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
struct TYPE_4__ {int length; scalar_t__ data; } ;
typedef  TYPE_1__ heim_bit_string ;

/* Variables and functions */
 int memcmp (scalar_t__,scalar_t__,int) ; 

int
der_heim_bit_string_cmp(const heim_bit_string *p,
			const heim_bit_string *q)
{
    int i, r1, r2;
    if (p->length != q->length)
	return p->length - q->length;
    i = memcmp(p->data, q->data, p->length / 8);
    if (i)
	return i;
    if ((p->length % 8) == 0)
	return 0;
    i = (p->length / 8);
    r1 = ((unsigned char *)p->data)[i];
    r2 = ((unsigned char *)q->data)[i];
    i = 8 - (p->length % 8);
    r1 = r1 >> i;
    r2 = r2 >> i;
    return r1 - r2;
}