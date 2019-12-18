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
typedef  int /*<<< orphan*/  isc_uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ isc_lfsr_t ;

/* Variables and functions */
 int /*<<< orphan*/  lfsr_generate (TYPE_1__*) ; 

__attribute__((used)) static inline isc_uint32_t
lfsr_skipgenerate(isc_lfsr_t *lfsr, unsigned int skip)
{
	while (skip--)
		(void)lfsr_generate(lfsr);

	(void)lfsr_generate(lfsr);

	return (lfsr->state);
}