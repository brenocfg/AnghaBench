#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  revs; } ;
typedef  TYPE_1__ bhnd_sprom_opcode_state ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SPROM_OP_BAD (TYPE_1__*,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ SPROM_OP_REV_MAX ; 
 int bhnd_sprom_opcode_clear_var (TYPE_1__*) ; 
 int /*<<< orphan*/  bit_nset (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline int
bhnd_sprom_opcode_set_revs(bhnd_sprom_opcode_state *state, uint8_t start,
    uint8_t end)
{
	int error;

	/* Validate the revision range */
	if (start > SPROM_OP_REV_MAX ||
	    end > SPROM_OP_REV_MAX ||
	    end < start)
	{
		SPROM_OP_BAD(state, "invalid revision range: %hhu-%hhu\n",
		    start, end);
		return (EINVAL);
	}

	/* Clear variable state */
	if ((error = bhnd_sprom_opcode_clear_var(state)))
		return (error);

	/* Reset revision mask */
	memset(state->revs, 0x0, sizeof(state->revs));
	bit_nset(state->revs, start, end);

	return (0);
}