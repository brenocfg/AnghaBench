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
struct TYPE_6__ {int* x; int wds; } ;
typedef  int Long ;
typedef  TYPE_1__ Bigint ;

/* Variables and functions */
 TYPE_1__* Balloc (struct dtoa_context*,int) ; 
 TYPE_1__* multadd (struct dtoa_context*,TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Bigint *
s2b
 (struct dtoa_context* C, const char *s, int nd0, int nd, ULong y9, int dplen)
{
	Bigint *b;
	int i, k;
	Long x, y;

	x = (nd + 8) / 9;
	for(k = 0, y = 1; x > y; y <<= 1, k++) ;
#ifdef Pack_32
	b = Balloc(C, k);
	b->x[0] = y9;
	b->wds = 1;
#else
	b = Balloc(C, k+1);
	b->x[0] = y9 & 0xffff;
	b->wds = (b->x[1] = y9 >> 16) ? 2 : 1;
#endif

	i = 9;
	if (9 < nd0) {
		s += 9;
		do b = multadd(C, b, 10, *s++ - '0');
			while(++i < nd0);
		s += dplen;
		}
	else
		s += dplen + 9;
	for(; i < nd; i++)
		b = multadd(C, b, 10, *s++ - '0');
	return b;
	}