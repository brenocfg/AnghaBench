#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
struct TYPE_15__ {scalar_t__* xyz; int* st; int* modulate; } ;
typedef  TYPE_5__ polyVert_t ;
struct TYPE_16__ {scalar_t__ type; scalar_t__ end; float time; scalar_t__* org; scalar_t__ start; int* vel; int alpha; int height; int width; float endtime; float endwidth; float endheight; scalar_t__ color; scalar_t__ startfade; double accumroll; int shaderAnim; int /*<<< orphan*/  pshader; scalar_t__ roll; scalar_t__ rotate; int /*<<< orphan*/  link; } ;
typedef  TYPE_6__ cparticle_t ;
struct TYPE_14__ {int /*<<< orphan*/ * viewaxis; } ;
struct TYPE_18__ {float time; TYPE_4__ refdef; TYPE_3__* snap; } ;
struct TYPE_11__ {scalar_t__ hardwareType; } ;
struct TYPE_17__ {TYPE_1__ glconfig; } ;
struct TYPE_12__ {int /*<<< orphan*/  origin; } ;
struct TYPE_13__ {TYPE_2__ ps; } ;

/* Variables and functions */
 int /*<<< orphan*/  AngleVectors (scalar_t__*,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 scalar_t__ BLOODRED ; 
 int /*<<< orphan*/  DEG2RAD (scalar_t__) ; 
 float Distance (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ EMISIVEFADE ; 
 scalar_t__ GLHW_RAGEPRO ; 
 scalar_t__ GREY75 ; 
 scalar_t__ P_ANIM ; 
 scalar_t__ P_BLEED ; 
 scalar_t__ P_BUBBLE ; 
 scalar_t__ P_BUBBLE_TURBULENT ; 
 scalar_t__ P_FLAT ; 
 scalar_t__ P_FLAT_SCALEUP ; 
 scalar_t__ P_SMOKE ; 
 scalar_t__ P_SMOKE_IMPACT ; 
 scalar_t__ P_SPRITE ; 
 scalar_t__ P_WEATHER ; 
 scalar_t__ P_WEATHER_FLURRY ; 
 scalar_t__ P_WEATHER_TURBULENT ; 
 size_t ROLL ; 
 int /*<<< orphan*/  VectorCopy (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  VectorMA (scalar_t__*,int,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  VectorSet (scalar_t__*,double,double,double) ; 
 TYPE_9__ cg ; 
 TYPE_8__ cgs ; 
 float cos (int /*<<< orphan*/ ) ; 
 int crandom () ; 
 scalar_t__ floor (float) ; 
 int /*<<< orphan*/  rforward ; 
 scalar_t__* rright ; 
 scalar_t__* rup ; 
 float* shaderAnimCounts ; 
 int /*<<< orphan*/ ** shaderAnims ; 
 float sin (int /*<<< orphan*/ ) ; 
 float sqrt (int) ; 
 int /*<<< orphan*/  trap_R_AddPolyToScene (int /*<<< orphan*/ ,int,TYPE_5__*) ; 
 int /*<<< orphan*/  vectoangles (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__* vright ; 
 scalar_t__* vup ; 

void CG_AddParticleToScene (cparticle_t *p, vec3_t org, float alpha)
{

	vec3_t		point;
	polyVert_t	verts[4];
	float		width;
	float		height;
	float		time, time2;
	float		ratio;
	float		invratio;
	vec3_t		color;
	polyVert_t	TRIverts[3];
	vec3_t		rright2, rup2;

	if (p->type == P_WEATHER || p->type == P_WEATHER_TURBULENT || p->type == P_WEATHER_FLURRY
		|| p->type == P_BUBBLE || p->type == P_BUBBLE_TURBULENT)
	{// create a front facing polygon
			
		if (p->type != P_WEATHER_FLURRY)
		{
			if (p->type == P_BUBBLE || p->type == P_BUBBLE_TURBULENT)
			{
				if (org[2] > p->end)			
				{	
					p->time = cg.time;	
					VectorCopy (org, p->org); // Ridah, fixes rare snow flakes that flicker on the ground
									
					p->org[2] = ( p->start + crandom () * 4 );
					
					
					if (p->type == P_BUBBLE_TURBULENT)
					{
						p->vel[0] = crandom() * 4;
						p->vel[1] = crandom() * 4;
					}
				
				}
			}
			else
			{
				if (org[2] < p->end)			
				{	
					p->time = cg.time;	
					VectorCopy (org, p->org); // Ridah, fixes rare snow flakes that flicker on the ground
									
					while (p->org[2] < p->end) 
					{
						p->org[2] += (p->start - p->end); 
					}
					
					
					if (p->type == P_WEATHER_TURBULENT)
					{
						p->vel[0] = crandom() * 16;
						p->vel[1] = crandom() * 16;
					}
				
				}
			}
			

			// Rafael snow pvs check
			if (!p->link)
				return;

			p->alpha = 1;
		}
		
		// Ridah, had to do this or MAX_POLYS is being exceeded in village1.bsp
		if (Distance( cg.snap->ps.origin, org ) > 1024) {
			return;
		}
		// done.
	
		if (p->type == P_BUBBLE || p->type == P_BUBBLE_TURBULENT)
		{
			VectorMA (org, -p->height, vup, point);	
			VectorMA (point, -p->width, vright, point);	
			VectorCopy (point, verts[0].xyz);	
			verts[0].st[0] = 0;	
			verts[0].st[1] = 0;	
			verts[0].modulate[0] = 255;	
			verts[0].modulate[1] = 255;	
			verts[0].modulate[2] = 255;	
			verts[0].modulate[3] = 255 * p->alpha;	

			VectorMA (org, -p->height, vup, point);	
			VectorMA (point, p->width, vright, point);	
			VectorCopy (point, verts[1].xyz);	
			verts[1].st[0] = 0;	
			verts[1].st[1] = 1;	
			verts[1].modulate[0] = 255;	
			verts[1].modulate[1] = 255;	
			verts[1].modulate[2] = 255;	
			verts[1].modulate[3] = 255 * p->alpha;	

			VectorMA (org, p->height, vup, point);	
			VectorMA (point, p->width, vright, point);	
			VectorCopy (point, verts[2].xyz);	
			verts[2].st[0] = 1;	
			verts[2].st[1] = 1;	
			verts[2].modulate[0] = 255;	
			verts[2].modulate[1] = 255;	
			verts[2].modulate[2] = 255;	
			verts[2].modulate[3] = 255 * p->alpha;	

			VectorMA (org, p->height, vup, point);	
			VectorMA (point, -p->width, vright, point);	
			VectorCopy (point, verts[3].xyz);	
			verts[3].st[0] = 1;	
			verts[3].st[1] = 0;	
			verts[3].modulate[0] = 255;	
			verts[3].modulate[1] = 255;	
			verts[3].modulate[2] = 255;	
			verts[3].modulate[3] = 255 * p->alpha;	
		}
		else
		{
			VectorMA (org, -p->height, vup, point);	
			VectorMA (point, -p->width, vright, point);	
			VectorCopy( point, TRIverts[0].xyz );
			TRIverts[0].st[0] = 1;
			TRIverts[0].st[1] = 0;
			TRIverts[0].modulate[0] = 255;
			TRIverts[0].modulate[1] = 255;
			TRIverts[0].modulate[2] = 255;
			TRIverts[0].modulate[3] = 255 * p->alpha;	

			VectorMA (org, p->height, vup, point);	
			VectorMA (point, -p->width, vright, point);	
			VectorCopy (point, TRIverts[1].xyz);	
			TRIverts[1].st[0] = 0;
			TRIverts[1].st[1] = 0;
			TRIverts[1].modulate[0] = 255;
			TRIverts[1].modulate[1] = 255;
			TRIverts[1].modulate[2] = 255;
			TRIverts[1].modulate[3] = 255 * p->alpha;	

			VectorMA (org, p->height, vup, point);	
			VectorMA (point, p->width, vright, point);	
			VectorCopy (point, TRIverts[2].xyz);	
			TRIverts[2].st[0] = 0;
			TRIverts[2].st[1] = 1;
			TRIverts[2].modulate[0] = 255;
			TRIverts[2].modulate[1] = 255;
			TRIverts[2].modulate[2] = 255;
			TRIverts[2].modulate[3] = 255 * p->alpha;	
		}
	
	}
	else if (p->type == P_SPRITE)
	{
		vec3_t	rr, ru;
		vec3_t	rotate_ang;

#ifdef WOLF_PARTICLES
		VectorSet (color, 1.0, 1.0, 1.0);
#else
		VectorSet (color, 1.0, 1.0, 0.5);
#endif
		time = cg.time - p->time;
		time2 = p->endtime - p->time;
		ratio = time / time2;

		width = p->width + ( ratio * ( p->endwidth - p->width) );
		height = p->height + ( ratio * ( p->endheight - p->height) );

		if (p->roll) {
			vectoangles( cg.refdef.viewaxis[0], rotate_ang );
			rotate_ang[ROLL] += p->roll;
			AngleVectors ( rotate_ang, NULL, rr, ru);
		}

		if (p->roll) {
			VectorMA (org, -height, ru, point);	
			VectorMA (point, -width, rr, point);	
		} else {
			VectorMA (org, -height, vup, point);	
			VectorMA (point, -width, vright, point);	
		}
		VectorCopy (point, verts[0].xyz);	
		verts[0].st[0] = 0;	
		verts[0].st[1] = 0;	
		verts[0].modulate[0] = 255;	
		verts[0].modulate[1] = 255;	
		verts[0].modulate[2] = 255;	
		verts[0].modulate[3] = 255;

		if (p->roll) {
			VectorMA (point, 2*height, ru, point);	
		} else {
			VectorMA (point, 2*height, vup, point);	
		}
		VectorCopy (point, verts[1].xyz);	
		verts[1].st[0] = 0;	
		verts[1].st[1] = 1;	
		verts[1].modulate[0] = 255;	
		verts[1].modulate[1] = 255;	
		verts[1].modulate[2] = 255;	
		verts[1].modulate[3] = 255;	

		if (p->roll) {
			VectorMA (point, 2*width, rr, point);	
		} else {
			VectorMA (point, 2*width, vright, point);	
		}
		VectorCopy (point, verts[2].xyz);	
		verts[2].st[0] = 1;	
		verts[2].st[1] = 1;	
		verts[2].modulate[0] = 255;	
		verts[2].modulate[1] = 255;	
		verts[2].modulate[2] = 255;	
		verts[2].modulate[3] = 255;	

		if (p->roll) {
			VectorMA (point, -2*height, ru, point);	
		} else {
			VectorMA (point, -2*height, vup, point);	
		}
		VectorCopy (point, verts[3].xyz);	
		verts[3].st[0] = 1;	
		verts[3].st[1] = 0;	
		verts[3].modulate[0] = 255;	
		verts[3].modulate[1] = 255;	
		verts[3].modulate[2] = 255;	
		verts[3].modulate[3] = 255;	
	}
	else if (p->type == P_SMOKE || p->type == P_SMOKE_IMPACT)
	{// create a front rotating facing polygon

		if ( p->type == P_SMOKE_IMPACT && Distance( cg.snap->ps.origin, org ) > 1024) {
			return;
		}

		if (p->color == BLOODRED)
			VectorSet (color, 0.22f, 0.0f, 0.0f);
		else if (p->color == GREY75)
		{
			float	len;
			float	greyit;
			float	val;
			len = Distance (cg.snap->ps.origin, org);
			if (!len)
				len = 1;

			val = 4096/len;
			greyit = 0.25 * val;
			if (greyit > 0.5)
				greyit = 0.5;

			VectorSet (color, greyit, greyit, greyit);
		}
		else
			VectorSet (color, 1.0, 1.0, 1.0);

		time = cg.time - p->time;
		time2 = p->endtime - p->time;
		ratio = time / time2;
		
		if (cg.time > p->startfade)
		{
			invratio = 1 - ( (cg.time - p->startfade) / (p->endtime - p->startfade) );

			if (p->color == EMISIVEFADE)
			{
				float fval;
				fval = (invratio * invratio);
				if (fval < 0)
					fval = 0;
				VectorSet (color, fval , fval , fval );
			}
			invratio *= p->alpha;
		}
		else 
			invratio = 1 * p->alpha;

		if ( cgs.glconfig.hardwareType == GLHW_RAGEPRO )
			invratio = 1;

		if (invratio > 1)
			invratio = 1;
	
		width = p->width + ( ratio * ( p->endwidth - p->width) );
		height = p->height + ( ratio * ( p->endheight - p->height) );

		if (p->type != P_SMOKE_IMPACT)
		{
			vec3_t temp;

			vectoangles (rforward, temp);
			p->accumroll += p->roll;
			temp[ROLL] += p->accumroll * 0.1;
			AngleVectors ( temp, NULL, rright2, rup2);
		}
		else
		{
			VectorCopy (rright, rright2);
			VectorCopy (rup, rup2);
		}
		
		if (p->rotate)
		{
			VectorMA (org, -height, rup2, point);	
			VectorMA (point, -width, rright2, point);	
		}
		else
		{
			VectorMA (org, -p->height, vup, point);	
			VectorMA (point, -p->width, vright, point);	
		}
		VectorCopy (point, verts[0].xyz);	
		verts[0].st[0] = 0;	
		verts[0].st[1] = 0;	
		verts[0].modulate[0] = 255 * color[0];	
		verts[0].modulate[1] = 255 * color[1];	
		verts[0].modulate[2] = 255 * color[2];	
		verts[0].modulate[3] = 255 * invratio;	

		if (p->rotate)
		{
			VectorMA (org, -height, rup2, point);	
			VectorMA (point, width, rright2, point);	
		}
		else
		{
			VectorMA (org, -p->height, vup, point);	
			VectorMA (point, p->width, vright, point);	
		}
		VectorCopy (point, verts[1].xyz);	
		verts[1].st[0] = 0;	
		verts[1].st[1] = 1;	
		verts[1].modulate[0] = 255 * color[0];	
		verts[1].modulate[1] = 255 * color[1];	
		verts[1].modulate[2] = 255 * color[2];	
		verts[1].modulate[3] = 255 * invratio;	

		if (p->rotate)
		{
			VectorMA (org, height, rup2, point);	
			VectorMA (point, width, rright2, point);	
		}
		else
		{
			VectorMA (org, p->height, vup, point);	
			VectorMA (point, p->width, vright, point);	
		}
		VectorCopy (point, verts[2].xyz);	
		verts[2].st[0] = 1;	
		verts[2].st[1] = 1;	
		verts[2].modulate[0] = 255 * color[0];	
		verts[2].modulate[1] = 255 * color[1];	
		verts[2].modulate[2] = 255 * color[2];	
		verts[2].modulate[3] = 255 * invratio;	

		if (p->rotate)
		{
			VectorMA (org, height, rup2, point);	
			VectorMA (point, -width, rright2, point);	
		}
		else
		{
			VectorMA (org, p->height, vup, point);	
			VectorMA (point, -p->width, vright, point);	
		}
		VectorCopy (point, verts[3].xyz);	
		verts[3].st[0] = 1;	
		verts[3].st[1] = 0;	
		verts[3].modulate[0] = 255 * color[0];	
		verts[3].modulate[1] = 255 * color[1];	
		verts[3].modulate[2] = 255 * color[2];	
		verts[3].modulate[3] = 255  * invratio;	
		
	}
	else if (p->type == P_BLEED)
	{
		vec3_t	rr, ru;
		vec3_t	rotate_ang;
		float	alpha;

		alpha = p->alpha;
		
		if ( cgs.glconfig.hardwareType == GLHW_RAGEPRO )
			alpha = 1;

		if (p->roll) 
		{
			vectoangles( cg.refdef.viewaxis[0], rotate_ang );
			rotate_ang[ROLL] += p->roll;
			AngleVectors ( rotate_ang, NULL, rr, ru);
		}
		else
		{
			VectorCopy (vup, ru);
			VectorCopy (vright, rr);
		}

		VectorMA (org, -p->height, ru, point);	
		VectorMA (point, -p->width, rr, point);	
		VectorCopy (point, verts[0].xyz);	
		verts[0].st[0] = 0;	
		verts[0].st[1] = 0;	
		verts[0].modulate[0] = 111;	
		verts[0].modulate[1] = 19;	
		verts[0].modulate[2] = 9;	
		verts[0].modulate[3] = 255 * alpha;	

		VectorMA (org, -p->height, ru, point);	
		VectorMA (point, p->width, rr, point);	
		VectorCopy (point, verts[1].xyz);	
		verts[1].st[0] = 0;	
		verts[1].st[1] = 1;	
		verts[1].modulate[0] = 111;	
		verts[1].modulate[1] = 19;	
		verts[1].modulate[2] = 9;	
		verts[1].modulate[3] = 255 * alpha;	

		VectorMA (org, p->height, ru, point);	
		VectorMA (point, p->width, rr, point);	
		VectorCopy (point, verts[2].xyz);	
		verts[2].st[0] = 1;	
		verts[2].st[1] = 1;	
		verts[2].modulate[0] = 111;	
		verts[2].modulate[1] = 19;	
		verts[2].modulate[2] = 9;	
		verts[2].modulate[3] = 255 * alpha;	

		VectorMA (org, p->height, ru, point);	
		VectorMA (point, -p->width, rr, point);	
		VectorCopy (point, verts[3].xyz);	
		verts[3].st[0] = 1;	
		verts[3].st[1] = 0;	
		verts[3].modulate[0] = 111;	
		verts[3].modulate[1] = 19;	
		verts[3].modulate[2] = 9;	
		verts[3].modulate[3] = 255 * alpha;	

	}
	else if (p->type == P_FLAT_SCALEUP)
	{
		float sinR, cosR;

		if (p->color == BLOODRED)
			VectorSet (color, 1, 1, 1);
		else
			VectorSet (color, 0.5, 0.5, 0.5);
		
		time = cg.time - p->time;
		time2 = p->endtime - p->time;
		ratio = time / time2;

		width = p->width + ( ratio * ( p->endwidth - p->width) );
		height = p->height + ( ratio * ( p->endheight - p->height) );

		if (width > p->endwidth)
			width = p->endwidth;

		if (height > p->endheight)
			height = p->endheight;

		sinR = height * sin(DEG2RAD(p->roll)) * sqrt(2);
		cosR = width * cos(DEG2RAD(p->roll)) * sqrt(2);

		VectorCopy (org, verts[0].xyz);	
		verts[0].xyz[0] -= sinR;
		verts[0].xyz[1] -= cosR;
		verts[0].st[0] = 0;	
		verts[0].st[1] = 0;	
		verts[0].modulate[0] = 255 * color[0];	
		verts[0].modulate[1] = 255 * color[1];	
		verts[0].modulate[2] = 255 * color[2];	
		verts[0].modulate[3] = 255;	

		VectorCopy (org, verts[1].xyz);	
		verts[1].xyz[0] -= cosR;	
		verts[1].xyz[1] += sinR;	
		verts[1].st[0] = 0;	
		verts[1].st[1] = 1;	
		verts[1].modulate[0] = 255 * color[0];	
		verts[1].modulate[1] = 255 * color[1];	
		verts[1].modulate[2] = 255 * color[2];	
		verts[1].modulate[3] = 255;	

		VectorCopy (org, verts[2].xyz);	
		verts[2].xyz[0] += sinR;	
		verts[2].xyz[1] += cosR;	
		verts[2].st[0] = 1;	
		verts[2].st[1] = 1;	
		verts[2].modulate[0] = 255 * color[0];	
		verts[2].modulate[1] = 255 * color[1];	
		verts[2].modulate[2] = 255 * color[2];	
		verts[2].modulate[3] = 255;	

		VectorCopy (org, verts[3].xyz);	
		verts[3].xyz[0] += cosR;	
		verts[3].xyz[1] -= sinR;	
		verts[3].st[0] = 1;	
		verts[3].st[1] = 0;	
		verts[3].modulate[0] = 255 * color[0];	
		verts[3].modulate[1] = 255 * color[1];	
		verts[3].modulate[2] = 255 * color[2];	
		verts[3].modulate[3] = 255;		
	}
	else if (p->type == P_FLAT)
	{

		VectorCopy (org, verts[0].xyz);	
		verts[0].xyz[0] -= p->height;	
		verts[0].xyz[1] -= p->width;	
		verts[0].st[0] = 0;	
		verts[0].st[1] = 0;	
		verts[0].modulate[0] = 255;	
		verts[0].modulate[1] = 255;	
		verts[0].modulate[2] = 255;	
		verts[0].modulate[3] = 255;	

		VectorCopy (org, verts[1].xyz);	
		verts[1].xyz[0] -= p->height;	
		verts[1].xyz[1] += p->width;	
		verts[1].st[0] = 0;	
		verts[1].st[1] = 1;	
		verts[1].modulate[0] = 255;	
		verts[1].modulate[1] = 255;	
		verts[1].modulate[2] = 255;	
		verts[1].modulate[3] = 255;	

		VectorCopy (org, verts[2].xyz);	
		verts[2].xyz[0] += p->height;	
		verts[2].xyz[1] += p->width;	
		verts[2].st[0] = 1;	
		verts[2].st[1] = 1;	
		verts[2].modulate[0] = 255;	
		verts[2].modulate[1] = 255;	
		verts[2].modulate[2] = 255;	
		verts[2].modulate[3] = 255;	

		VectorCopy (org, verts[3].xyz);	
		verts[3].xyz[0] += p->height;	
		verts[3].xyz[1] -= p->width;	
		verts[3].st[0] = 1;	
		verts[3].st[1] = 0;	
		verts[3].modulate[0] = 255;	
		verts[3].modulate[1] = 255;	
		verts[3].modulate[2] = 255;	
		verts[3].modulate[3] = 255;	

	}
	// Ridah
	else if (p->type == P_ANIM) {
		vec3_t	rr, ru;
		vec3_t	rotate_ang;
		int i, j;

		time = cg.time - p->time;
		time2 = p->endtime - p->time;
		ratio = time / time2;
		if (ratio >= 1.0f) {
			ratio = 0.9999f;
		}

		width = p->width + ( ratio * ( p->endwidth - p->width) );
		height = p->height + ( ratio * ( p->endheight - p->height) );

		// if we are "inside" this sprite, don't draw
		if (Distance( cg.snap->ps.origin, org ) < width/1.5) {
			return;
		}

		i = p->shaderAnim;
		j = (int)floor(ratio * shaderAnimCounts[p->shaderAnim]);
		p->pshader = shaderAnims[i][j];

		if (p->roll) {
			vectoangles( cg.refdef.viewaxis[0], rotate_ang );
			rotate_ang[ROLL] += p->roll;
			AngleVectors ( rotate_ang, NULL, rr, ru);
		}

		if (p->roll) {
			VectorMA (org, -height, ru, point);	
			VectorMA (point, -width, rr, point);	
		} else {
			VectorMA (org, -height, vup, point);	
			VectorMA (point, -width, vright, point);	
		}
		VectorCopy (point, verts[0].xyz);	
		verts[0].st[0] = 0;	
		verts[0].st[1] = 0;	
		verts[0].modulate[0] = 255;	
		verts[0].modulate[1] = 255;	
		verts[0].modulate[2] = 255;	
		verts[0].modulate[3] = 255;

		if (p->roll) {
			VectorMA (point, 2*height, ru, point);	
		} else {
			VectorMA (point, 2*height, vup, point);	
		}
		VectorCopy (point, verts[1].xyz);	
		verts[1].st[0] = 0;	
		verts[1].st[1] = 1;	
		verts[1].modulate[0] = 255;	
		verts[1].modulate[1] = 255;	
		verts[1].modulate[2] = 255;	
		verts[1].modulate[3] = 255;	

		if (p->roll) {
			VectorMA (point, 2*width, rr, point);	
		} else {
			VectorMA (point, 2*width, vright, point);	
		}
		VectorCopy (point, verts[2].xyz);	
		verts[2].st[0] = 1;	
		verts[2].st[1] = 1;	
		verts[2].modulate[0] = 255;	
		verts[2].modulate[1] = 255;	
		verts[2].modulate[2] = 255;	
		verts[2].modulate[3] = 255;	

		if (p->roll) {
			VectorMA (point, -2*height, ru, point);	
		} else {
			VectorMA (point, -2*height, vup, point);	
		}
		VectorCopy (point, verts[3].xyz);	
		verts[3].st[0] = 1;	
		verts[3].st[1] = 0;	
		verts[3].modulate[0] = 255;	
		verts[3].modulate[1] = 255;	
		verts[3].modulate[2] = 255;	
		verts[3].modulate[3] = 255;	
	}
	// done.
	
	if (!p->pshader) {
// (SA) temp commented out for DM
//		CG_Printf ("CG_AddParticleToScene type %d p->pshader == ZERO\n", p->type);
		return;
	}

	if (p->type == P_WEATHER || p->type == P_WEATHER_TURBULENT || p->type == P_WEATHER_FLURRY)
		trap_R_AddPolyToScene( p->pshader, 3, TRIverts );
	else
		trap_R_AddPolyToScene( p->pshader, 4, verts );

}