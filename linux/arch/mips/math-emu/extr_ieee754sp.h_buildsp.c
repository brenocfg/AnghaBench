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
union ieee754sp {int sign; int bexp; unsigned int mant; } ;

/* Variables and functions */
 int SP_EBIAS ; 
 int SP_EMAX ; 
 int SP_EMIN ; 
 unsigned int SP_FBITS ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline union ieee754sp buildsp(int s, int bx, unsigned int m)
{
	union ieee754sp r;

	assert((s) == 0 || (s) == 1);
	assert((bx) >= SP_EMIN - 1 + SP_EBIAS
	       && (bx) <= SP_EMAX + 1 + SP_EBIAS);
	assert(((m) >> SP_FBITS) == 0);

	r.sign = s;
	r.bexp = bx;
	r.mant = m;

	return r;
}