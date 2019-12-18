#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {float f; int /*<<< orphan*/  i; } ;
typedef  TYPE_1__ _FloatByteUnion ;

/* Variables and functions */
 int /*<<< orphan*/  LongSwap (int /*<<< orphan*/ ) ; 

float FloatSwap (const float *f) {
	_FloatByteUnion out;

	out.f = *f;
	out.i = LongSwap(out.i);

	return out.f;
}