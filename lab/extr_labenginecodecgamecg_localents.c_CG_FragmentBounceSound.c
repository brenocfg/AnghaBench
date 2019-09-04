#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  endpos; } ;
typedef  TYPE_2__ trace_t ;
typedef  int /*<<< orphan*/  sfxHandle_t ;
struct TYPE_9__ {scalar_t__ leBounceSoundType; } ;
typedef  TYPE_3__ localEntity_t ;
struct TYPE_7__ {int /*<<< orphan*/  gibBounce3Sound; int /*<<< orphan*/  gibBounce2Sound; int /*<<< orphan*/  gibBounce1Sound; } ;
struct TYPE_10__ {TYPE_1__ media; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAN_AUTO ; 
 int /*<<< orphan*/  ENTITYNUM_WORLD ; 
 scalar_t__ LEBS_BLOOD ; 
 scalar_t__ LEBS_BRASS ; 
 scalar_t__ LEBS_NONE ; 
 TYPE_4__ cgs ; 
 int rand () ; 
 int /*<<< orphan*/  trap_S_StartSound (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void CG_FragmentBounceSound( localEntity_t *le, trace_t *trace ) {
	if ( le->leBounceSoundType == LEBS_BLOOD ) {
		// half the gibs will make splat sounds
		if ( rand() & 1 ) {
			int r = rand()&3;
			sfxHandle_t	s;

			if ( r == 0 ) {
				s = cgs.media.gibBounce1Sound;
			} else if ( r == 1 ) {
				s = cgs.media.gibBounce2Sound;
			} else {
				s = cgs.media.gibBounce3Sound;
			}
			trap_S_StartSound( trace->endpos, ENTITYNUM_WORLD, CHAN_AUTO, s );
		}
	} else if ( le->leBounceSoundType == LEBS_BRASS ) {

	}

	// don't allow a fragment to make multiple bounce sounds,
	// or it gets too noisy as they settle
	le->leBounceSoundType = LEBS_NONE;
}