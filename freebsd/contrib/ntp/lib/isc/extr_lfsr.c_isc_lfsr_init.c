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
typedef  scalar_t__ isc_uint32_t ;
typedef  int /*<<< orphan*/  (* isc_lfsrreseed_t ) (TYPE_1__*,void*) ;
struct TYPE_6__ {int state; unsigned int bits; unsigned int count; void* arg; int /*<<< orphan*/  (* reseed ) (TYPE_1__*,void*) ;scalar_t__ tap; } ;
typedef  TYPE_1__ isc_lfsr_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE (int) ; 
 int VALID_LFSR (TYPE_1__*) ; 

void
isc_lfsr_init(isc_lfsr_t *lfsr, isc_uint32_t state, unsigned int bits,
	      isc_uint32_t tap, unsigned int count,
	      isc_lfsrreseed_t reseed, void *arg)
{
	REQUIRE(VALID_LFSR(lfsr));
	REQUIRE(8 <= bits && bits <= 32);
	REQUIRE(tap != 0);

	lfsr->state = state;
	lfsr->bits = bits;
	lfsr->tap = tap;
	lfsr->count = count;
	lfsr->reseed = reseed;
	lfsr->arg = arg;

	if (count == 0 && reseed != NULL)
		reseed(lfsr, arg);
	if (lfsr->state == 0)
		lfsr->state = 0xffffffffU >> (32 - lfsr->bits);
}