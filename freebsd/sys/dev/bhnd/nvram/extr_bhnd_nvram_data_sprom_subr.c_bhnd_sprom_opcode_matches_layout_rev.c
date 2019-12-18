#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* layout; int /*<<< orphan*/  revs; } ;
typedef  TYPE_2__ bhnd_sprom_opcode_state ;
struct TYPE_4__ {int /*<<< orphan*/  rev; } ;

/* Variables and functions */
 int bit_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
bhnd_sprom_opcode_matches_layout_rev(bhnd_sprom_opcode_state *state)
{
	return (bit_test(state->revs, state->layout->rev));
}