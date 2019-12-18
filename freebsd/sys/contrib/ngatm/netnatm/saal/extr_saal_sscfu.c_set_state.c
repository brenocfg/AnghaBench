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
struct sscfu {size_t state; int /*<<< orphan*/  aarg; } ;
typedef  enum sscfu_state { ____Placeholder_sscfu_state } sscfu_state ;

/* Variables and functions */
 int /*<<< orphan*/  SSCFU_DBG_STATE ; 
 int /*<<< orphan*/  VERBOSE (struct sscfu*,int /*<<< orphan*/ ,struct sscfu*) ; 
 int /*<<< orphan*/ * sscf_states ; 

__attribute__((used)) static __inline void
set_state(struct sscfu *sscf, enum sscfu_state state)
{
	VERBOSE(sscf, SSCFU_DBG_STATE, (sscf, sscf->aarg,
	    "change state from %s to %s",
	    sscf_states[sscf->state], sscf_states[state]));
	sscf->state = state;
}