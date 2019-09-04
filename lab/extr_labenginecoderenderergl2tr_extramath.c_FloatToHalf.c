#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int fraction; int /*<<< orphan*/  sign; scalar_t__ exponent; } ;
union f32_u {float f; TYPE_1__ pack; } ;
struct TYPE_4__ {int fraction; int /*<<< orphan*/  sign; int /*<<< orphan*/  exponent; } ;
union f16_u {int /*<<< orphan*/  ui; TYPE_2__ pack; } ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLAMP (int,int /*<<< orphan*/ ,int) ; 

uint16_t FloatToHalf(float in)
{
	union f32_u f32;
	union f16_u f16;

	f32.f = in;

	f16.pack.exponent = CLAMP((int)(f32.pack.exponent) - 112, 0, 31);
	f16.pack.fraction = f32.pack.fraction >> 13;
	f16.pack.sign     = f32.pack.sign;

	return f16.ui;
}