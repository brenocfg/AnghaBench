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
typedef  int BN_ULONG ;

/* Variables and functions */
 int BN_MASK2 ; 
 int /*<<< orphan*/  assert (int) ; 

BN_ULONG bn_add_words(BN_ULONG *r, BN_ULONG *a, BN_ULONG *b, int n)
	{
	BN_ULONG c,l,t;

	assert(n >= 0);
	if (n <= 0) return((BN_ULONG)0);

	c=0;
	for (;;)
		{
		t=a[0];
		t=(t+c)&BN_MASK2;
		c=(t < c);
		l=(t+b[0])&BN_MASK2;
		c+=(l < t);
		r[0]=l;
		if (--n <= 0) break;

		t=a[1];
		t=(t+c)&BN_MASK2;
		c=(t < c);
		l=(t+b[1])&BN_MASK2;
		c+=(l < t);
		r[1]=l;
		if (--n <= 0) break;

		t=a[2];
		t=(t+c)&BN_MASK2;
		c=(t < c);
		l=(t+b[2])&BN_MASK2;
		c+=(l < t);
		r[2]=l;
		if (--n <= 0) break;

		t=a[3];
		t=(t+c)&BN_MASK2;
		c=(t < c);
		l=(t+b[3])&BN_MASK2;
		c+=(l < t);
		r[3]=l;
		if (--n <= 0) break;

		a+=4;
		b+=4;
		r+=4;
		}
	return((BN_ULONG)c);
	}