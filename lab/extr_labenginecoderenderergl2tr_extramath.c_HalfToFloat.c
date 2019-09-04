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
struct TYPE_3__ {int exponent; int fraction; int /*<<< orphan*/  sign; } ;
union f32_u {float f; TYPE_1__ pack; } ;
struct TYPE_4__ {int fraction; int /*<<< orphan*/  sign; scalar_t__ exponent; } ;
union f16_u {TYPE_2__ pack; int /*<<< orphan*/  ui; } ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */

float HalfToFloat(uint16_t in)
{
	union f32_u f32;
	union f16_u f16;

	f16.ui = in;

	f32.pack.exponent = (int)(f16.pack.exponent) + 112;
	f32.pack.fraction = f16.pack.fraction << 13;
	f32.pack.sign = f16.pack.sign;

	return f32.f;
}