#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int top; int* d; } ;
typedef  int BN_ULONG ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int BN_MASK2 ; 
 int /*<<< orphan*/  bn_check_top (TYPE_1__ const*) ; 
 int /*<<< orphan*/  bn_fix_top (TYPE_1__*) ; 
 int bn_sub_words (int*,int*,int*,int) ; 
 int /*<<< orphan*/ * bn_wexpand (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

int BN_usub(BIGNUM *r, const BIGNUM *a, const BIGNUM *b)
	{
	int max,min;
	register BN_ULONG t1,t2,*ap,*bp,*rp;
	int i,carry;
#if defined(IRIX_CC_BUG) && !defined(LINT)
	int dummy;
#endif

	bn_check_top(a);
	bn_check_top(b);

	if (a->top < b->top) /* hmm... should not be happening */
		{
		return(0);
		}

	max=a->top;
	min=b->top;
	if (bn_wexpand(r,max) == NULL) return(0);

	ap=a->d;
	bp=b->d;
	rp=r->d;

#if 1
	carry=0;
	for (i=0; i<min; i++)
		{
		t1= *(ap++);
		t2= *(bp++);
		if (carry)
			{
			carry=(t1 <= t2);
			t1=(t1-t2-1)&BN_MASK2;
			}
		else
			{
			carry=(t1 < t2);
			t1=(t1-t2)&BN_MASK2;
			}
#if defined(IRIX_CC_BUG) && !defined(LINT)
		dummy=t1;
#endif
		*(rp++)=t1&BN_MASK2;
		}
#else
	carry=bn_sub_words(rp,ap,bp,min);
	ap+=min;
	bp+=min;
	rp+=min;
	i=min;
#endif
	if (carry) /* subtracted */
		{
		while (i < max)
			{
			i++;
			t1= *(ap++);
			t2=(t1-1)&BN_MASK2;
			*(rp++)=t2;
			if (t1 > t2) break;
			}
		}
#if 0
	memcpy(rp,ap,sizeof(*rp)*(max-i));
#else
	if (rp != ap)
		{
		for (;;)
			{
			if (i++ >= max) break;
			rp[0]=ap[0];
			if (i++ >= max) break;
			rp[1]=ap[1];
			if (i++ >= max) break;
			rp[2]=ap[2];
			if (i++ >= max) break;
			rp[3]=ap[3];
			rp+=4;
			ap+=4;
			}
		}
#endif

	r->top=max;
	bn_fix_top(r);
	return(1);
	}