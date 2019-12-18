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
struct dtoa_context {int dummy; } ;
typedef  int ULong ;
typedef  int ULLong ;
struct TYPE_6__ {int wds; int k; int maxwds; int* x; } ;
typedef  TYPE_1__ Bigint ;

/* Variables and functions */
 TYPE_1__* Balloc (struct dtoa_context*,int) ; 
 int FFFFFFFF ; 
 int /*<<< orphan*/  Storeinc (int*,int,int) ; 

__attribute__((used)) static Bigint *
mult
 (struct dtoa_context* C, Bigint *a, Bigint *b)
{
	Bigint *c;
	int k, wa, wb, wc;
	ULong *x, *xa, *xae, *xb, *xbe, *xc, *xc0;
	ULong y;
#ifdef ULLong
	ULLong carry, z;
#else
	ULong carry, z;
#ifdef Pack_32
	ULong z2;
#endif
#endif

	if (a->wds < b->wds) {
		c = a;
		a = b;
		b = c;
		}
	k = a->k;
	wa = a->wds;
	wb = b->wds;
	wc = wa + wb;
	if (wc > a->maxwds)
		k++;
	c = Balloc(C, k);
	for(x = c->x, xa = x + wc; x < xa; x++)
		*x = 0;
	xa = a->x;
	xae = xa + wa;
	xb = b->x;
	xbe = xb + wb;
	xc0 = c->x;
#ifdef ULLong
	for(; xb < xbe; xc0++) {
		if ((y = *xb++)) {
			x = xa;
			xc = xc0;
			carry = 0;
			do {
				z = *x++ * (ULLong)y + *xc + carry;
				carry = z >> 32;
				*xc++ = z & FFFFFFFF;
				}
				while(x < xae);
			*xc = carry;
			}
		}
#else
#ifdef Pack_32
	for(; xb < xbe; xb++, xc0++) {
		if (y = *xb & 0xffff) {
			x = xa;
			xc = xc0;
			carry = 0;
			do {
				z = (*x & 0xffff) * y + (*xc & 0xffff) + carry;
				carry = z >> 16;
				z2 = (*x++ >> 16) * y + (*xc >> 16) + carry;
				carry = z2 >> 16;
				Storeinc(xc, z2, z);
				}
				while(x < xae);
			*xc = carry;
			}
		if (y = *xb >> 16) {
			x = xa;
			xc = xc0;
			carry = 0;
			z2 = *xc;
			do {
				z = (*x & 0xffff) * y + (*xc >> 16) + carry;
				carry = z >> 16;
				Storeinc(xc, z, z2);
				z2 = (*x++ >> 16) * y + (*xc & 0xffff) + carry;
				carry = z2 >> 16;
				}
				while(x < xae);
			*xc = z2;
			}
		}
#else
	for(; xb < xbe; xc0++) {
		if (y = *xb++) {
			x = xa;
			xc = xc0;
			carry = 0;
			do {
				z = *x++ * y + *xc + carry;
				carry = z >> 16;
				*xc++ = z & 0xffff;
				}
				while(x < xae);
			*xc = carry;
			}
		}
#endif
#endif
	for(xc0 = c->x, xc = xc0 + wc; wc > 0 && !*--xc; --wc) ;
	c->wds = wc;
	return c;
	}