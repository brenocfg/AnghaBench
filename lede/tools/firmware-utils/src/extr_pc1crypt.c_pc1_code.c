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
struct pc1_ctx {int dx; int x1a2; size_t i; int ax; int* x1a0; int cx; int bx; int tmp; int si; int res; } ;

/* Variables and functions */

__attribute__((used)) static void pc1_code(struct pc1_ctx *pc1)
{
	pc1->dx = pc1->x1a2 + pc1->i;
	pc1->ax = pc1->x1a0[pc1->i];
	pc1->cx = 0x015a;
	pc1->bx = 0x4e35;

	pc1->tmp = pc1->ax;
	pc1->ax = pc1->si;
	pc1->si = pc1->tmp;

	pc1->tmp = pc1->ax;
	pc1->ax = pc1->dx;
	pc1->dx = pc1->tmp;

	if (pc1->ax != 0) {
		pc1->ax = pc1->ax * pc1->bx;
	}

	pc1->tmp = pc1->ax;
	pc1->ax = pc1->cx;
	pc1->cx = pc1->tmp;

	if (pc1->ax != 0) {
		pc1->ax = pc1->ax * pc1->si;
		pc1->cx = pc1->ax + pc1->cx;
	}

	pc1->tmp = pc1->ax;
	pc1->ax = pc1->si;
	pc1->si = pc1->tmp;
	pc1->ax = pc1->ax * pc1->bx;
	pc1->dx = pc1->cx + pc1->dx;

	pc1->ax = pc1->ax + 1;

	pc1->x1a2 = pc1->dx;
	pc1->x1a0[pc1->i] = pc1->ax;

	pc1->res = pc1->ax ^ pc1->dx;
	pc1->i = pc1->i + 1;
}