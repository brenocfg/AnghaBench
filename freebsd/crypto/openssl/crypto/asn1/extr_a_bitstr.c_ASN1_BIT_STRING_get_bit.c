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
struct TYPE_3__ {int length; int* data; } ;
typedef  TYPE_1__ ASN1_BIT_STRING ;

/* Variables and functions */

int ASN1_BIT_STRING_get_bit(const ASN1_BIT_STRING *a, int n)
{
    int w, v;

    w = n / 8;
    v = 1 << (7 - (n & 0x07));
    if ((a == NULL) || (a->length < (w + 1)) || (a->data == NULL))
        return 0;
    return ((a->data[w] & v) != 0);
}