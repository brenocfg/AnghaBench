#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int type; } ;
typedef  TYPE_1__ ASN1_INTEGER ;

/* Variables and functions */
 int ASN1_STRING_cmp (TYPE_1__ const*,TYPE_1__ const*) ; 
 int V_ASN1_NEG ; 

int ASN1_INTEGER_cmp(const ASN1_INTEGER *x, const ASN1_INTEGER *y)
{
    int neg, ret;
    /* Compare signs */
    neg = x->type & V_ASN1_NEG;
    if (neg != (y->type & V_ASN1_NEG)) {
        if (neg)
            return -1;
        else
            return 1;
    }

    ret = ASN1_STRING_cmp(x, y);

    if (neg)
        return -ret;
    else
        return ret;
}