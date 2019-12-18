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
struct TYPE_6__ {int neg; int top; int* d; } ;
typedef  int BN_ULONG ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int BN_MASK2 ; 
 int /*<<< orphan*/  BN_is_zero (TYPE_1__*) ; 
 int BN_sub_word (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * bn_wexpand (TYPE_1__*,int) ; 

int BN_add_word(BIGNUM *a, BN_ULONG w)
	{
	BN_ULONG l;
	int i;

	if (a->neg)
		{
		a->neg=0;
		i=BN_sub_word(a,w);
		if (!BN_is_zero(a))
			a->neg=!(a->neg);
		return(i);
		}
	w&=BN_MASK2;
	if (bn_wexpand(a,a->top+1) == NULL) return(0);
	i=0;
	for (;;)
		{
		l=(a->d[i]+(BN_ULONG)w)&BN_MASK2;
		a->d[i]=l;
		if (w > l)
			w=1;
		else
			break;
		i++;
		}
	if (i >= a->top)
		a->top++;
	return(1);
	}