#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ULong ;
struct TYPE_6__ {int* us; } ;
typedef  TYPE_1__ U ;
struct TYPE_8__ {int sign; int* bits; int kind; int ex; int /*<<< orphan*/  gdtoa; TYPE_2__* fpi; } ;
struct TYPE_7__ {int member_0; int member_1; int member_2; int member_3; int /*<<< orphan*/  member_4; } ;
typedef  TYPE_2__ FPI ;
typedef  TYPE_3__ FPBits ;

/* Variables and functions */
 int STRTOG_Denormal ; 
 int STRTOG_Infinite ; 
 int STRTOG_NaN ; 
 int STRTOG_Normal ; 
 int STRTOG_Zero ; 
 size_t _0 ; 
 size_t _1 ; 
 size_t _2 ; 
 size_t _3 ; 
 size_t _4 ; 
 int /*<<< orphan*/  gdtoa ; 

__attribute__((used)) static void
xfpbits(U *u, FPBits *b)
{
	ULong *bits;
	int ex, i;
	static FPI fpi0 = { 64, 1-16383-64+1, 32766 - 16383 - 64 + 1, 1, 0 };

	b->fpi = &fpi0;
	b->gdtoa = gdtoa;
	b->sign = u->us[_0] & 0x8000;
	bits = b->bits;
	bits[1] = (u->us[_1] << 16) | u->us[_2];
	bits[0] = (u->us[_3] << 16) | u->us[_4];
	if ( (ex = u->us[_0] & 0x7fff) !=0) {
		i = STRTOG_Normal;
		if (ex == 0x7fff)
			/* Infinity or NaN */
			i = bits[0] | bits[1] ? STRTOG_NaN : STRTOG_Infinite;
		}
	else if (bits[0] | bits[1]) {
		i = STRTOG_Denormal;
		ex = 1;
		}
	else
		i = STRTOG_Zero;
	b->kind = i;
	b->ex = ex - (0x3fff + 63);
	}