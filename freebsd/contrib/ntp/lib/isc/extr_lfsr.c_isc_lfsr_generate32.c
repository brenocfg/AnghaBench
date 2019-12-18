#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int isc_uint32_t ;
struct TYPE_6__ {int state; } ;
typedef  TYPE_1__ isc_lfsr_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALID_LFSR (TYPE_1__*) ; 
 int lfsr_skipgenerate (TYPE_1__*,int) ; 

isc_uint32_t
isc_lfsr_generate32(isc_lfsr_t *lfsr1, isc_lfsr_t *lfsr2)
{
	isc_uint32_t state1, state2;
	isc_uint32_t skip1, skip2;

	REQUIRE(VALID_LFSR(lfsr1));
	REQUIRE(VALID_LFSR(lfsr2));

	skip1 = lfsr1->state & 0x01;
	skip2 = lfsr2->state & 0x01;

	/* cross-skip. */
	state1 = lfsr_skipgenerate(lfsr1, skip2);
	state2 = lfsr_skipgenerate(lfsr2, skip1);

	return (state1 ^ state2);
}