#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  double* vec3_t ;
typedef  scalar_t__ sfxHandle_t ;
typedef  scalar_t__ qhandle_t ;
typedef  int qboolean ;
struct TYPE_8__ {int* shaderRGBA; } ;
struct TYPE_11__ {float light; int* lightColor; int* color; TYPE_1__ refEntity; } ;
typedef  TYPE_4__ localEntity_t ;
typedef  int /*<<< orphan*/  impactSound_t ;
struct TYPE_13__ {int /*<<< orphan*/  integer; } ;
struct TYPE_10__ {scalar_t__ holeMarkShader; scalar_t__ dishFlashModel; scalar_t__ grenadeExplosionShader; scalar_t__ burnMarkShader; scalar_t__ rocketExplosionShader; scalar_t__ ringFlashModel; scalar_t__ railExplosionShader; scalar_t__ energyMarkShader; scalar_t__ plasmaExplosionShader; scalar_t__ bfgExplosionShader; scalar_t__ bulletFlashModel; scalar_t__ bulletExplosionShader; scalar_t__ bulletMarkShader; scalar_t__ sfx_ric3; scalar_t__ sfx_ric2; scalar_t__ sfx_ric1; scalar_t__ sfx_chghit; scalar_t__ sfx_chghitmetal; scalar_t__ sfx_chghitflesh; scalar_t__ sfx_rockexp; scalar_t__ sfx_plasmaexp; scalar_t__ sfx_proxexp; scalar_t__ sfx_lghit3; scalar_t__ sfx_lghit1; scalar_t__ sfx_lghit2; scalar_t__ sfx_nghit; scalar_t__ sfx_nghitmetal; scalar_t__ sfx_nghitflesh; } ;
struct TYPE_12__ {TYPE_2__* clientinfo; TYPE_3__ media; } ;
struct TYPE_9__ {double* color1; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_ImpactMark (scalar_t__,double*,double*,int,int,int,int,int,int,float,int) ; 
 TYPE_4__* CG_MakeExplosion (double*,double*,scalar_t__,scalar_t__,int,int) ; 
 int /*<<< orphan*/  CG_ParticleExplosion (char*,double*,double*,int,int,int) ; 
 int /*<<< orphan*/  CHAN_AUTO ; 
 int /*<<< orphan*/  ENTITYNUM_WORLD ; 
 int /*<<< orphan*/  IMPACTSOUND_FLESH ; 
 int /*<<< orphan*/  IMPACTSOUND_METAL ; 
 int /*<<< orphan*/  VectorCopy (double*,int*) ; 
 int /*<<< orphan*/  VectorMA (double*,int,double*,double*) ; 
 int /*<<< orphan*/  VectorScale (double*,int,double*) ; 
#define  WP_BFG 138 
#define  WP_CHAINGUN 137 
#define  WP_GRENADE_LAUNCHER 136 
#define  WP_LIGHTNING 135 
#define  WP_MACHINEGUN 134 
#define  WP_NAILGUN 133 
#define  WP_PLASMAGUN 132 
#define  WP_PROX_LAUNCHER 131 
#define  WP_RAILGUN 130 
#define  WP_ROCKET_LAUNCHER 129 
#define  WP_SHOTGUN 128 
 TYPE_6__ cg_oldRocket ; 
 TYPE_5__ cgs ; 
 int qfalse ; 
 int qtrue ; 
 int rand () ; 
 int random () ; 
 int /*<<< orphan*/  trap_S_StartSound (double*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void CG_MissileHitWall( int weapon, int clientNum, vec3_t origin, vec3_t dir, impactSound_t soundType ) {
	qhandle_t		mod;
	qhandle_t		mark;
	qhandle_t		shader;
	sfxHandle_t		sfx;
	float			radius;
	float			light;
	vec3_t			lightColor;
	localEntity_t	*le;
	int				r;
	qboolean		alphaFade;
	qboolean		isSprite;
	int				duration;
	vec3_t			sprOrg;
	vec3_t			sprVel;

	mod = 0;
	shader = 0;
	light = 0;
	lightColor[0] = 1;
	lightColor[1] = 1;
	lightColor[2] = 0;

	// set defaults
	isSprite = qfalse;
	duration = 600;

	switch ( weapon ) {
	default:
#ifdef MISSIONPACK
	case WP_NAILGUN:
		if( soundType == IMPACTSOUND_FLESH ) {
			sfx = cgs.media.sfx_nghitflesh;
		} else if( soundType == IMPACTSOUND_METAL ) {
			sfx = cgs.media.sfx_nghitmetal;
		} else {
			sfx = cgs.media.sfx_nghit;
		}
		mark = cgs.media.holeMarkShader;
		radius = 12;
		break;
#endif
	case WP_LIGHTNING:
		// no explosion at LG impact, it is added with the beam
		r = rand() & 3;
		if ( r < 2 ) {
			sfx = cgs.media.sfx_lghit2;
		} else if ( r == 2 ) {
			sfx = cgs.media.sfx_lghit1;
		} else {
			sfx = cgs.media.sfx_lghit3;
		}
		mark = cgs.media.holeMarkShader;
		radius = 12;
		break;
#ifdef MISSIONPACK
	case WP_PROX_LAUNCHER:
		mod = cgs.media.dishFlashModel;
		shader = cgs.media.grenadeExplosionShader;
		sfx = cgs.media.sfx_proxexp;
		mark = cgs.media.burnMarkShader;
		radius = 64;
		light = 300;
		isSprite = qtrue;
		break;
#endif
	case WP_GRENADE_LAUNCHER:
		mod = cgs.media.dishFlashModel;
		shader = cgs.media.grenadeExplosionShader;
		sfx = cgs.media.sfx_rockexp;
		mark = cgs.media.burnMarkShader;
		radius = 64;
		light = 300;
		isSprite = qtrue;
		break;
	case WP_ROCKET_LAUNCHER:
		mod = cgs.media.dishFlashModel;
		shader = cgs.media.rocketExplosionShader;
		sfx = cgs.media.sfx_rockexp;
		mark = cgs.media.burnMarkShader;
		radius = 64;
		light = 300;
		isSprite = qtrue;
		duration = 1000;
		lightColor[0] = 1;
		lightColor[1] = 0.75;
		lightColor[2] = 0.0;
		if (cg_oldRocket.integer == 0) {
			// explosion sprite animation
			VectorMA( origin, 24, dir, sprOrg );
			VectorScale( dir, 64, sprVel );

			CG_ParticleExplosion( "explode1", sprOrg, sprVel, 1400, 20, 30 );
		}
		break;
	case WP_RAILGUN:
		mod = cgs.media.ringFlashModel;
		shader = cgs.media.railExplosionShader;
		//sfx = cgs.media.sfx_railg;
		sfx = cgs.media.sfx_plasmaexp;
		mark = cgs.media.energyMarkShader;
		radius = 24;
		break;
	case WP_PLASMAGUN:
		mod = cgs.media.ringFlashModel;
		shader = cgs.media.plasmaExplosionShader;
		sfx = cgs.media.sfx_plasmaexp;
		mark = cgs.media.energyMarkShader;
		radius = 16;
		break;
	case WP_BFG:
		mod = cgs.media.dishFlashModel;
		shader = cgs.media.bfgExplosionShader;
		sfx = cgs.media.sfx_rockexp;
		mark = cgs.media.burnMarkShader;
		radius = 32;
		isSprite = qtrue;
		break;
	case WP_SHOTGUN:
		mod = cgs.media.bulletFlashModel;
		shader = cgs.media.bulletExplosionShader;
		mark = cgs.media.bulletMarkShader;
		sfx = 0;
		radius = 4;
		break;

#ifdef MISSIONPACK
	case WP_CHAINGUN:
		mod = cgs.media.bulletFlashModel;
		if( soundType == IMPACTSOUND_FLESH ) {
			sfx = cgs.media.sfx_chghitflesh;
		} else if( soundType == IMPACTSOUND_METAL ) {
			sfx = cgs.media.sfx_chghitmetal;
		} else {
			sfx = cgs.media.sfx_chghit;
		}
		mark = cgs.media.bulletMarkShader;

		radius = 8;
		break;
#endif

	case WP_MACHINEGUN:
		mod = cgs.media.bulletFlashModel;
		shader = cgs.media.bulletExplosionShader;
		mark = cgs.media.bulletMarkShader;

		r = rand() & 3;
		if ( r == 0 ) {
			sfx = cgs.media.sfx_ric1;
		} else if ( r == 1 ) {
			sfx = cgs.media.sfx_ric2;
		} else {
			sfx = cgs.media.sfx_ric3;
		}

		radius = 8;
		break;
	}

	if ( sfx ) {
		trap_S_StartSound( origin, ENTITYNUM_WORLD, CHAN_AUTO, sfx );
	}

	//
	// create the explosion
	//
	if ( mod ) {
		le = CG_MakeExplosion( origin, dir, 
							   mod,	shader,
							   duration, isSprite );
		le->light = light;
		VectorCopy( lightColor, le->lightColor );
		if ( weapon == WP_RAILGUN ) {
			// colorize with client color
			VectorCopy( cgs.clientinfo[clientNum].color1, le->color );
			le->refEntity.shaderRGBA[0] = le->color[0] * 0xff;
			le->refEntity.shaderRGBA[1] = le->color[1] * 0xff;
			le->refEntity.shaderRGBA[2] = le->color[2] * 0xff;
			le->refEntity.shaderRGBA[3] = 0xff;
		}
	}

	//
	// impact mark
	//
	alphaFade = (mark == cgs.media.energyMarkShader);	// plasma fades alpha, all others fade color
	if ( weapon == WP_RAILGUN ) {
		float	*color;

		// colorize with client color
		color = cgs.clientinfo[clientNum].color1;
		CG_ImpactMark( mark, origin, dir, random()*360, color[0],color[1], color[2],1, alphaFade, radius, qfalse );
	} else {
		CG_ImpactMark( mark, origin, dir, random()*360, 1,1,1,1, alphaFade, radius, qfalse );
	}
}