#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  normal; } ;
struct TYPE_10__ {TYPE_2__ plane; int /*<<< orphan*/  endpos; } ;
typedef  TYPE_3__ trace_t ;
struct TYPE_11__ {scalar_t__ leMarkType; } ;
typedef  TYPE_4__ localEntity_t ;
struct TYPE_8__ {int /*<<< orphan*/  burnMarkShader; int /*<<< orphan*/  bloodMarkShader; } ;
struct TYPE_12__ {TYPE_1__ media; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_ImpactMark (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ LEMT_BLOOD ; 
 scalar_t__ LEMT_BURN ; 
 scalar_t__ LEMT_NONE ; 
 TYPE_5__ cgs ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int rand () ; 
 int random () ; 

void CG_FragmentBounceMark( localEntity_t *le, trace_t *trace ) {
	int			radius;

	if ( le->leMarkType == LEMT_BLOOD ) {

		radius = 16 + (rand()&31);
		CG_ImpactMark( cgs.media.bloodMarkShader, trace->endpos, trace->plane.normal, random()*360,
			1,1,1,1, qtrue, radius, qfalse );
	} else if ( le->leMarkType == LEMT_BURN ) {

		radius = 8 + (rand()&15);
		CG_ImpactMark( cgs.media.burnMarkShader, trace->endpos, trace->plane.normal, random()*360,
			1,1,1,1, qtrue, radius, qfalse );
	}


	// don't allow a fragment to make multiple marks, or they
	// pile up while settling
	le->leMarkType = LEMT_NONE;
}