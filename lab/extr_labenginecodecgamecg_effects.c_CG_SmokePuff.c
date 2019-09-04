#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_12__ {int rotation; float radius; int shaderTime; int* shaderRGBA; int /*<<< orphan*/  reType; int /*<<< orphan*/  customShader; int /*<<< orphan*/  origin; } ;
typedef  TYPE_4__ refEntity_t ;
typedef  int /*<<< orphan*/  qhandle_t ;
struct TYPE_9__ {int trTime; int /*<<< orphan*/  trBase; int /*<<< orphan*/  trDelta; int /*<<< orphan*/  trType; } ;
struct TYPE_13__ {int leFlags; float radius; int startTime; int fadeInTime; int endTime; double lifeRate; float* color; TYPE_1__ pos; int /*<<< orphan*/  leType; TYPE_4__ refEntity; } ;
typedef  TYPE_5__ localEntity_t ;
struct TYPE_11__ {int /*<<< orphan*/  smokePuffRageProShader; } ;
struct TYPE_10__ {scalar_t__ hardwareType; } ;
struct TYPE_14__ {TYPE_3__ media; TYPE_2__ glconfig; } ;

/* Variables and functions */
 TYPE_5__* CG_AllocLocalEntity () ; 
 scalar_t__ GLHW_RAGEPRO ; 
 int /*<<< orphan*/  LE_MOVE_SCALE_FADE ; 
 int Q_random (int*) ; 
 int /*<<< orphan*/  RT_SPRITE ; 
 int /*<<< orphan*/  TR_LINEAR ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 TYPE_6__ cgs ; 

localEntity_t *CG_SmokePuff( const vec3_t p, const vec3_t vel, 
				   float radius,
				   float r, float g, float b, float a,
				   float duration,
				   int startTime,
				   int fadeInTime,
				   int leFlags,
				   qhandle_t hShader ) {
	static int	seed = 0x92;
	localEntity_t	*le;
	refEntity_t		*re;
//	int fadeInTime = startTime + duration / 2;

	le = CG_AllocLocalEntity();
	le->leFlags = leFlags;
	le->radius = radius;

	re = &le->refEntity;
	re->rotation = Q_random( &seed ) * 360;
	re->radius = radius;
	re->shaderTime = startTime / 1000.0f;

	le->leType = LE_MOVE_SCALE_FADE;
	le->startTime = startTime;
	le->fadeInTime = fadeInTime;
	le->endTime = startTime + duration;
	if ( fadeInTime > startTime ) {
		le->lifeRate = 1.0 / ( le->endTime - le->fadeInTime );
	}
	else {
		le->lifeRate = 1.0 / ( le->endTime - le->startTime );
	}
	le->color[0] = r;
	le->color[1] = g; 
	le->color[2] = b;
	le->color[3] = a;


	le->pos.trType = TR_LINEAR;
	le->pos.trTime = startTime;
	VectorCopy( vel, le->pos.trDelta );
	VectorCopy( p, le->pos.trBase );

	VectorCopy( p, re->origin );
	re->customShader = hShader;

	// rage pro can't alpha fade, so use a different shader
	if ( cgs.glconfig.hardwareType == GLHW_RAGEPRO ) {
		re->customShader = cgs.media.smokePuffRageProShader;
		re->shaderRGBA[0] = 0xff;
		re->shaderRGBA[1] = 0xff;
		re->shaderRGBA[2] = 0xff;
		re->shaderRGBA[3] = 0xff;
	} else {
		re->shaderRGBA[0] = le->color[0] * 0xff;
		re->shaderRGBA[1] = le->color[1] * 0xff;
		re->shaderRGBA[2] = le->color[2] * 0xff;
		re->shaderRGBA[3] = 0xff;
	}

	re->reType = RT_SPRITE;
	re->radius = le->radius;

	return le;
}