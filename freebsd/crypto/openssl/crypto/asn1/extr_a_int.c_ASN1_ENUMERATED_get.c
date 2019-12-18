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
typedef  scalar_t__ int64_t ;
struct TYPE_4__ {int type; int length; } ;
typedef  TYPE_1__ ASN1_ENUMERATED ;

/* Variables and functions */
 int ASN1_ENUMERATED_get_int64 (scalar_t__*,TYPE_1__ const*) ; 
 scalar_t__ LONG_MAX ; 
 scalar_t__ LONG_MIN ; 
 int V_ASN1_ENUMERATED ; 
 int V_ASN1_NEG ; 

long ASN1_ENUMERATED_get(const ASN1_ENUMERATED *a)
{
    int i;
    int64_t r;
    if (a == NULL)
        return 0;
    if ((a->type & ~V_ASN1_NEG) != V_ASN1_ENUMERATED)
        return -1;
    if (a->length > (int)sizeof(long))
        return 0xffffffffL;
    i = ASN1_ENUMERATED_get_int64(&r, a);
    if (i == 0)
        return -1;
    if (r > LONG_MAX || r < LONG_MIN)
        return -1;
    return (long)r;
}