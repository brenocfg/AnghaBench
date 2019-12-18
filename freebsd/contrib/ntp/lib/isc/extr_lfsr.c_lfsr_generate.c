#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int isc_uint32_t ;
struct TYPE_4__ {int state; int bits; int tap; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* reseed ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ isc_lfsr_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline isc_uint32_t
lfsr_generate(isc_lfsr_t *lfsr)
{

	/*
	 * If the previous state is zero, we must fill it with something
	 * here, or we will begin to generate an extremely predictable output.
	 *
	 * First, give the reseed function a crack at it.  If the state is
	 * still 0, set it to all ones.
	 */
	if (lfsr->state == 0) {
		if (lfsr->reseed != NULL)
			lfsr->reseed(lfsr, lfsr->arg);
		if (lfsr->state == 0)
			lfsr->state = 0xffffffffU >> (32 - lfsr->bits);
	}

	if (lfsr->state & 0x01) {
		lfsr->state = (lfsr->state >> 1) ^ lfsr->tap;
		return (1);
	} else {
		lfsr->state >>= 1;
		return (0);
	}
}