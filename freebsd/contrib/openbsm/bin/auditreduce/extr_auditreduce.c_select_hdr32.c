#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_5__ {scalar_t__ e_type; scalar_t__ s; } ;
struct TYPE_6__ {TYPE_1__ hdr32; } ;
struct TYPE_7__ {TYPE_2__ tt; } ;
typedef  TYPE_3__ tokenstr_t ;
typedef  int /*<<< orphan*/  time_t ;

/* Variables and functions */
 int /*<<< orphan*/  AU_PRS_BOTH ; 
 int /*<<< orphan*/  AU_PRS_USECACHE ; 
 scalar_t__ ISOPTSET (int /*<<< orphan*/ ,int) ; 
 int OPT_A ; 
 int OPT_a ; 
 int OPT_b ; 
 int OPT_c ; 
 int OPT_m ; 
 int OPT_v ; 
 int /*<<< orphan*/  SETOPT (int /*<<< orphan*/ ,int) ; 
 int au_preselect (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ difftime (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maskp ; 
 int /*<<< orphan*/  opttochk ; 
 int /*<<< orphan*/  p_atime ; 
 int /*<<< orphan*/  p_btime ; 
 scalar_t__* p_evec ; 
 size_t p_evec_used ; 

__attribute__((used)) static int
select_hdr32(tokenstr_t tok, uint32_t *optchkd)
{
	uint16_t *ev;
	int match;

	SETOPT((*optchkd), (OPT_A | OPT_a | OPT_b | OPT_c | OPT_m | OPT_v));

	/* The A option overrides a, b and d. */
	if (!ISOPTSET(opttochk, OPT_A)) {
		if (ISOPTSET(opttochk, OPT_a)) {
			if (difftime((time_t)tok.tt.hdr32.s, p_atime) < 0) {
				/* Record was created before p_atime. */
				return (0);
			}
		}

		if (ISOPTSET(opttochk, OPT_b)) {
			if (difftime(p_btime, (time_t)tok.tt.hdr32.s) < 0) {
				/* Record was created after p_btime. */
				return (0);
			}
		}
	}

	if (ISOPTSET(opttochk, OPT_c)) {
		/*
		 * Check if the classes represented by the event matches
		 * given class.
		 */
		if (au_preselect(tok.tt.hdr32.e_type, &maskp, AU_PRS_BOTH,
		    AU_PRS_USECACHE) != 1)
			return (0);
	}

	/* Check if event matches. */
	if (ISOPTSET(opttochk, OPT_m)) {
		match = 0;
		for (ev = p_evec; ev < &p_evec[p_evec_used]; ev++)
			if (tok.tt.hdr32.e_type == *ev)
				match = 1;
		if (match == 0)
			return (0);
	}
		
	return (1);
}