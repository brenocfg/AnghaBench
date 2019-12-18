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
typedef  scalar_t__ u_int8_t ;
typedef  int u_int32_t ;
struct TYPE_3__ {int rounds; } ;
typedef  TYPE_1__ cast_key ;

/* Variables and functions */
 int /*<<< orphan*/  F1 (int,int,int) ; 
 int /*<<< orphan*/  F2 (int,int,int) ; 
 int /*<<< orphan*/  F3 (int,int,int) ; 
 scalar_t__ U_INT8_Ta (int) ; 
 scalar_t__ U_INT8_Tb (int) ; 
 scalar_t__ U_INT8_Tc (int) ; 
 scalar_t__ U_INT8_Td (int) ; 

void cast_encrypt(cast_key* key, u_int8_t* inblock, u_int8_t* outblock)
{
u_int32_t t, l, r;

	/* Get inblock into l,r */
	l = ((u_int32_t)inblock[0] << 24) | ((u_int32_t)inblock[1] << 16) |
	 ((u_int32_t)inblock[2] << 8) | (u_int32_t)inblock[3];
	r = ((u_int32_t)inblock[4] << 24) | ((u_int32_t)inblock[5] << 16) |
	 ((u_int32_t)inblock[6] << 8) | (u_int32_t)inblock[7];
	/* Do the work */
	F1(l, r,  0);
	F2(r, l,  1);
	F3(l, r,  2);
	F1(r, l,  3);
	F2(l, r,  4);
	F3(r, l,  5);
	F1(l, r,  6);
	F2(r, l,  7);
	F3(l, r,  8);
	F1(r, l,  9);
	F2(l, r, 10);
	F3(r, l, 11);
	/* Only do full 16 rounds if key length > 80 bits */
	if (key->rounds > 12) {
		F1(l, r, 12);
		F2(r, l, 13);
		F3(l, r, 14);
		F1(r, l, 15);
	}
	/* Put l,r into outblock */
	outblock[0] = U_INT8_Ta(r);
	outblock[1] = U_INT8_Tb(r);
	outblock[2] = U_INT8_Tc(r);
	outblock[3] = U_INT8_Td(r);
	outblock[4] = U_INT8_Ta(l);
	outblock[5] = U_INT8_Tb(l);
	outblock[6] = U_INT8_Tc(l);
	outblock[7] = U_INT8_Td(l);
	/* Wipe clean */
	t = l = r = 0;
}