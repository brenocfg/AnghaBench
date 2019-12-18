#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int top; int* d; } ;
typedef  int BN_ULONG ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int BN_BITS2 ; 
 int /*<<< orphan*/  bn_check_top (TYPE_1__*) ; 
 int /*<<< orphan*/  bn_correct_top (TYPE_1__*) ; 

int BN_clear_bit(BIGNUM *a, int n)
{
    int i, j;

    bn_check_top(a);
    if (n < 0)
        return 0;

    i = n / BN_BITS2;
    j = n % BN_BITS2;
    if (a->top <= i)
        return 0;

    a->d[i] &= (~(((BN_ULONG)1) << j));
    bn_correct_top(a);
    return 1;
}