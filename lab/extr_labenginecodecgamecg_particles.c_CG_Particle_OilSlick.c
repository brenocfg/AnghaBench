#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ qhandle_t ;
struct TYPE_9__ {int time; int endtime; int startfade; double alpha; int roll; int width; int height; int endheight; int endwidth; double snum; double* org; int /*<<< orphan*/  rotate; int /*<<< orphan*/  accel; scalar_t__* vel; int /*<<< orphan*/  type; scalar_t__ pshader; scalar_t__ alphavel; struct TYPE_9__* next; } ;
typedef  TYPE_2__ cparticle_t ;
struct TYPE_8__ {int* angles2; int /*<<< orphan*/  origin; } ;
struct TYPE_10__ {TYPE_1__ currentState; } ;
typedef  TYPE_3__ centity_t ;
struct TYPE_11__ {int time; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_Printf (char*) ; 
 int /*<<< orphan*/  P_FLAT_SCALEUP ; 
 int /*<<< orphan*/  VectorClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,double*) ; 
 TYPE_2__* active_particles ; 
 TYPE_5__ cg ; 
 double crandom () ; 
 TYPE_2__* free_particles ; 
 int /*<<< orphan*/  qfalse ; 
 int rand () ; 

void CG_Particle_OilSlick (qhandle_t pshader, centity_t *cent)
{
	cparticle_t	*p;
	
  	if (!pshader)
		CG_Printf ("CG_Particle_OilSlick == ZERO!\n");

	if (!free_particles)
		return;
	p = free_particles;
	free_particles = p->next;
	p->next = active_particles;
	active_particles = p;
	p->time = cg.time;
	
	if (cent->currentState.angles2[2])
		p->endtime = cg.time + cent->currentState.angles2[2];
	else
		p->endtime = cg.time + 60000;

	p->startfade = p->endtime;

	p->alpha = 1.0;
	p->alphavel = 0;
	p->roll = 0;

	p->pshader = pshader;

	if (cent->currentState.angles2[0] || cent->currentState.angles2[1])
	{
		p->width = cent->currentState.angles2[0];
		p->height = cent->currentState.angles2[0];

		p->endheight = cent->currentState.angles2[1];
		p->endwidth = cent->currentState.angles2[1];
	}
	else
	{
		p->width = 8;
		p->height = 8;

		p->endheight = 16;
		p->endwidth = 16;
	}

	p->type = P_FLAT_SCALEUP;

	p->snum = 1.0;

	VectorCopy(cent->currentState.origin, p->org );
	
	p->org[2]+= 0.55 + (crandom() * 0.5);

	p->vel[0] = 0;
	p->vel[1] = 0;
	p->vel[2] = 0;
	VectorClear( p->accel );

	p->rotate = qfalse;

	p->roll = rand()%179;
	
	p->alpha = 0.75;

}