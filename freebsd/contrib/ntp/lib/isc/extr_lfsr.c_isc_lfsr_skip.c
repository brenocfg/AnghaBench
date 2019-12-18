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
typedef  int /*<<< orphan*/  isc_lfsr_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALID_LFSR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lfsr_generate (int /*<<< orphan*/ *) ; 

void
isc_lfsr_skip(isc_lfsr_t *lfsr, unsigned int skip)
{
	REQUIRE(VALID_LFSR(lfsr));

	while (skip--)
		(void)lfsr_generate(lfsr);
}