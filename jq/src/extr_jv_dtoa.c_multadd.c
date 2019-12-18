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
struct dtoa_context {int dummy; } ;
typedef  int ULong ;
typedef  int ULLong ;
struct TYPE_8__ {int wds; int* x; int maxwds; scalar_t__ k; } ;
typedef  TYPE_1__ Bigint ;

/* Variables and functions */
 TYPE_1__* Balloc (struct dtoa_context*,scalar_t__) ; 
 int /*<<< orphan*/  Bcopy (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  Bfree (struct dtoa_context*,TYPE_1__*) ; 
 int FFFFFFFF ; 

__attribute__((used)) static Bigint *
multadd
 (struct dtoa_context* C, Bigint *b, int m, int a)	/* multiply by m and add a */
{
	int i, wds;
#ifdef ULLong
	ULong *x;
	ULLong carry, y;
#else
	ULong carry, *x, y;
#ifdef Pack_32
	ULong xi, z;
#endif
#endif
	Bigint *b1;

	wds = b->wds;
	x = b->x;
	i = 0;
	carry = a;
	do {
#ifdef ULLong
		y = *x * (ULLong)m + carry;
		carry = y >> 32;
		*x++ = y & FFFFFFFF;
#else
#ifdef Pack_32
		xi = *x;
		y = (xi & 0xffff) * m + carry;
		z = (xi >> 16) * m + (y >> 16);
		carry = z >> 16;
		*x++ = (z << 16) + (y & 0xffff);
#else
		y = *x * m + carry;
		carry = y >> 16;
		*x++ = y & 0xffff;
#endif
#endif
		}
		while(++i < wds);
	if (carry) {
		if (wds >= b->maxwds) {
			b1 = Balloc(C, b->k+1);
			Bcopy(b1, b);
			Bfree(C, b);
			b = b1;
			}
		b->x[wds++] = carry;
		b->wds = wds;
		}
	return b;
	}