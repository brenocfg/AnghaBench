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
typedef  size_t u_int ;
struct sscop {size_t state; int /*<<< orphan*/  sigs; int /*<<< orphan*/  saved_sigs; int /*<<< orphan*/  aarg; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGQ_MOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSCOP_DBG_STATE ; 
 int /*<<< orphan*/  VERBOSE (struct sscop*,int /*<<< orphan*/ ,struct sscop*) ; 
 int /*<<< orphan*/ * states ; 

__attribute__((used)) static void
sscop_set_state(struct sscop *sscop, u_int nstate)
{
	VERBOSE(sscop, SSCOP_DBG_STATE, (sscop, sscop->aarg,
	    "changing state from %s to %s",
	    states[sscop->state], states[nstate]));

	sscop->state = nstate;
	SIGQ_MOVE(&sscop->saved_sigs, &sscop->sigs);
}