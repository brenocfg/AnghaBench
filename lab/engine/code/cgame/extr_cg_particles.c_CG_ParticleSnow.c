#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void** vec3_t ;
typedef  scalar_t__ qhandle_t ;
struct TYPE_5__ {float alpha; int start; int end; int height; int width; int* vel; int snum; int /*<<< orphan*/  link; scalar_t__* accel; scalar_t__* org; int /*<<< orphan*/  type; scalar_t__ pshader; scalar_t__ alphavel; scalar_t__ color; int /*<<< orphan*/  time; struct TYPE_5__* next; } ;
typedef  TYPE_1__ cparticle_t ;
struct TYPE_6__ {int /*<<< orphan*/  time; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_Printf (char*) ; 
 int /*<<< orphan*/  P_WEATHER ; 
 int /*<<< orphan*/  P_WEATHER_TURBULENT ; 
 int /*<<< orphan*/  VectorCopy (void**,scalar_t__*) ; 
 TYPE_1__* active_particles ; 
 TYPE_3__ cg ; 
 int crandom () ; 
 TYPE_1__* free_particles ; 
 int /*<<< orphan*/  qtrue ; 

void CG_ParticleSnow (qhandle_t pshader, vec3_t origin, vec3_t origin2, int turb, float range, int snum)
{
	cparticle_t	*p;

	if (!pshader)
		CG_Printf ("CG_ParticleSnow pshader == ZERO!\n");

	if (!free_particles)
		return;
	p = free_particles;
	free_particles = p->next;
	p->next = active_particles;
	active_particles = p;
	p->time = cg.time;
	p->color = 0;
	p->alpha = 0.40f;
	p->alphavel = 0;
	p->start = origin[2];
	p->end = origin2[2];
	p->pshader = pshader;
	p->height = 1;
	p->width = 1;
	
	p->vel[2] = -50;

	if (turb)
	{
		p->type = P_WEATHER_TURBULENT;
		p->vel[2] = -50 * 1.3;
	}
	else
	{
		p->type = P_WEATHER;
	}
	
	VectorCopy(origin, p->org);

	p->org[0] = p->org[0] + ( crandom() * range);
	p->org[1] = p->org[1] + ( crandom() * range);
	p->org[2] = p->org[2] + ( crandom() * (p->start - p->end)); 

	p->vel[0] = p->vel[1] = 0;
	
	p->accel[0] = p->accel[1] = p->accel[2] = 0;

	if (turb)
	{
		p->vel[0] = crandom() * 16;
		p->vel[1] = crandom() * 16;
	}

	// Rafael snow pvs check
	p->snum = snum;
	p->link = qtrue;

}