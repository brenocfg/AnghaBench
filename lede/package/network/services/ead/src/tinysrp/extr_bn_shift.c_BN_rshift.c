#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int top; int* d; int /*<<< orphan*/  neg; } ;
typedef  int BN_ULONG ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int BN_BITS2 ; 
 int BN_MASK2 ; 
 int /*<<< orphan*/  BN_zero (TYPE_1__*) ; 
 int /*<<< orphan*/  bn_fix_top (TYPE_1__*) ; 
 int /*<<< orphan*/ * bn_wexpand (TYPE_1__*,int) ; 

int BN_rshift(BIGNUM *r, BIGNUM *a, int n)
	{
	int i,j,nw,lb,rb;
	BN_ULONG *t,*f;
	BN_ULONG l,tmp;

	nw=n/BN_BITS2;
	rb=n%BN_BITS2;
	lb=BN_BITS2-rb;
	if (nw > a->top || a->top == 0)
		{
		BN_zero(r);
		return(1);
		}
	if (r != a)
		{
		r->neg=a->neg;
		if (bn_wexpand(r,a->top-nw+1) == NULL) return(0);
		}

	f= &(a->d[nw]);
	t=r->d;
	j=a->top-nw;
	r->top=j;

	if (rb == 0)
		{
		for (i=j+1; i > 0; i--)
			*(t++)= *(f++);
		}
	else
		{
		l= *(f++);
		for (i=1; i<j; i++)
			{
			tmp =(l>>rb)&BN_MASK2;
			l= *(f++);
			*(t++) =(tmp|(l<<lb))&BN_MASK2;
			}
		*(t++) =(l>>rb)&BN_MASK2;
		}
	*t=0;
	bn_fix_top(r);
	return(1);
	}