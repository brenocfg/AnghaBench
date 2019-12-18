#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct TYPE_3__ {int** S; int* P; } ;
typedef  TYPE_1__ blf_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  BLFRND (int*,int*,int,int,int) ; 

void
Blowfish_decipher(blf_ctx *c, u_int32_t *xl, u_int32_t *xr)
{
	u_int32_t Xl;
	u_int32_t Xr;
	u_int32_t *s = c->S[0];
	u_int32_t *p = c->P;

	Xl = *xl;
	Xr = *xr;

	Xl ^= p[17];
	BLFRND(s, p, Xr, Xl, 16); BLFRND(s, p, Xl, Xr, 15);
	BLFRND(s, p, Xr, Xl, 14); BLFRND(s, p, Xl, Xr, 13);
	BLFRND(s, p, Xr, Xl, 12); BLFRND(s, p, Xl, Xr, 11);
	BLFRND(s, p, Xr, Xl, 10); BLFRND(s, p, Xl, Xr, 9);
	BLFRND(s, p, Xr, Xl, 8); BLFRND(s, p, Xl, Xr, 7);
	BLFRND(s, p, Xr, Xl, 6); BLFRND(s, p, Xl, Xr, 5);
	BLFRND(s, p, Xr, Xl, 4); BLFRND(s, p, Xl, Xr, 3);
	BLFRND(s, p, Xr, Xl, 2); BLFRND(s, p, Xl, Xr, 1);

	*xl = Xr ^ p[0];
	*xr = Xl;
}