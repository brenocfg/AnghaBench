#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ULong ;
struct TYPE_5__ {int* bits; int ex; scalar_t__ sign; TYPE_1__* fpi; } ;
struct TYPE_4__ {int rounding; } ;
typedef  TYPE_1__ FPI ;
typedef  TYPE_2__ FPBits ;

/* Variables and functions */
 int FPI_Round_down ; 
#define  FPI_Round_near 129 
#define  FPI_Round_up 128 
 int FPI_Round_zero ; 

__attribute__((used)) static int
bround(FPBits *b, int prec, int prec1)	/* round to prec hex digits after the "." */
{					/* prec1 = incoming precision (after ".") */
	FPI *fpi = b->fpi;
	ULong *bits, t;
	int i, inc, j, k, m, n;
#ifdef Honor_FLT_ROUNDS
	int rounding = fpi->rounding;

	if (rounding > FPI_Round_near && b->sign)
		rounding = FPI_Round_up + FPI_Round_down - rounding;
	if (rounding == FPI_Round_down)
		rounding = FPI_Round_zero;
#endif
	m = prec1 - prec;
	bits = b->bits;
	inc = 0;
#ifdef Honor_FLT_ROUNDS
	switch(rounding) {
		case FPI_Round_up:
			for(i = 0; i < m; i += 8)
				if (bits[i>>3])
					goto inc1;
			if ((j = i - m) > 0 && bits[(i-8)>>3] << j*4)
				goto inc1;
			break;
		case FPI_Round_near:
#endif
			k = m - 1;
			if ((t = bits[k >> 3] >> (j = (k&7)*4)) & 8) {
				if (t & 7)
					goto inc1;
				if (j && bits[k >> 3] << (32 - j))
					goto inc1;
				while(k >= 8) {
					k -= 8;
					if (bits[k>>3]) {
 inc1:
						inc = 1;
						goto haveinc;
						}
					}
				}
#ifdef Honor_FLT_ROUNDS
		}
#endif
 haveinc:
	b->ex += m*4;
	i = m >> 3;
	k = prec1 >> 3;
	j = i;
	if ((n = 4*(m & 7)))
		for(;; ++j) {
			bits[j-i] = bits[j] >> n;
			if (j == k)
				break;
			bits[j-i] |= bits[j+1] << (32-n);
			}
	else
		for(;; ++j) {
			bits[j-i] = bits[j];
			if (j == k)
				break;
			}
	k = prec >> 3;
	if (inc) {
		for(j = 0; !(++bits[j] & 0xffffffff); ++j);
		if (j > k) {
 onebit:
			bits[0] = 1;
			b->ex += 4*prec;
			return 1;
			}
		if ((j = prec & 7) < 7 && bits[k] >> (j+1)*4)
			goto onebit;
		}
	for(i = 0; !(bits[i >> 3] & (0xf << 4*(i&7))); ++i);
	if (i) {
		b->ex += 4*i;
		prec -= i;
		j = i >> 3;
		i &= 7;
		i *= 4;
		for(m = j; ; ++m) {
			bits[m-j] = bits[m] >> i;
			if (m == k)
				break;
			bits[m-j] |= bits[m+1] << (32 - i);
			}
		}
	return prec;
	}