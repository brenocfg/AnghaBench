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
struct streebog_uint512 {int* qword; } ;

/* Variables and functions */

__attribute__((used)) static void streebog_xor(const struct streebog_uint512 *x,
			 const struct streebog_uint512 *y,
			 struct streebog_uint512 *z)
{
	z->qword[0] = x->qword[0] ^ y->qword[0];
	z->qword[1] = x->qword[1] ^ y->qword[1];
	z->qword[2] = x->qword[2] ^ y->qword[2];
	z->qword[3] = x->qword[3] ^ y->qword[3];
	z->qword[4] = x->qword[4] ^ y->qword[4];
	z->qword[5] = x->qword[5] ^ y->qword[5];
	z->qword[6] = x->qword[6] ^ y->qword[6];
	z->qword[7] = x->qword[7] ^ y->qword[7];
}