#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {float shadeAngleDegrees; double vertexScale; void* lmCustomHeight; void* lmCustomWidth; int /*<<< orphan*/  mod; void* notjunc; void* forceSunlight; int /*<<< orphan*/  vertexShadows; void* patchShadows; int /*<<< orphan*/  lightmapSampleOffset; scalar_t__ lightmapSampleSize; void* polygonOffset; int /*<<< orphan*/  lightStyle; int /*<<< orphan*/  bounceScale; int /*<<< orphan*/  backsplashDistance; int /*<<< orphan*/  backsplashFraction; int /*<<< orphan*/  compileFlags; int /*<<< orphan*/  surfaceFlags; int /*<<< orphan*/  contentFlags; } ;
typedef  TYPE_1__ shaderInfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  ApplySurfaceParm (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DEFAULT_LIGHTMAP_SAMPLE_OFFSET ; 
 int /*<<< orphan*/  DEF_BACKSPLASH_DISTANCE ; 
 int /*<<< orphan*/  DEF_BACKSPLASH_FRACTION ; 
 int /*<<< orphan*/  DEF_RADIOSITY_BOUNCE ; 
 int /*<<< orphan*/  Error (char*) ; 
 int /*<<< orphan*/  LS_NORMAL ; 
 int MAX_SHADER_INFO ; 
 int /*<<< orphan*/  TCModIdentity (int /*<<< orphan*/ ) ; 
 void* lmCustomSize ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int numShaderInfo ; 
 void* qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_1__* safe_malloc (int) ; 
 TYPE_1__* shaderInfo ; 

__attribute__((used)) static shaderInfo_t *AllocShaderInfo( void ){
	shaderInfo_t    *si;


	/* allocate? */
	if ( shaderInfo == NULL ) {
		shaderInfo = safe_malloc( sizeof( shaderInfo_t ) * MAX_SHADER_INFO );
		numShaderInfo = 0;
	}

	/* bounds check */
	if ( numShaderInfo == MAX_SHADER_INFO ) {
		Error( "MAX_SHADER_INFO exceeded. Remove some PK3 files or shader scripts from shaderlist.txt and try again." );
	}
	si = &shaderInfo[ numShaderInfo ];
	numShaderInfo++;

	/* ydnar: clear to 0 first */
	memset( si, 0, sizeof( shaderInfo_t ) );

	/* set defaults */
	ApplySurfaceParm( "default", &si->contentFlags, &si->surfaceFlags, &si->compileFlags );

	si->backsplashFraction = DEF_BACKSPLASH_FRACTION;
	si->backsplashDistance = DEF_BACKSPLASH_DISTANCE;

	si->bounceScale = DEF_RADIOSITY_BOUNCE;

	si->lightStyle = LS_NORMAL;

	si->polygonOffset = qfalse;

	si->shadeAngleDegrees = 0.0f;
	si->lightmapSampleSize = 0;
	si->lightmapSampleOffset = DEFAULT_LIGHTMAP_SAMPLE_OFFSET;
	si->patchShadows = qfalse;
	si->vertexShadows = qtrue;  /* ydnar: changed default behavior */
	si->forceSunlight = qfalse;
	si->vertexScale = 1.0;
	si->notjunc = qfalse;

	/* ydnar: set texture coordinate transform matrix to identity */
	TCModIdentity( si->mod );

	/* ydnar: lightmaps can now be > 128x128 in certain games or an externally generated tga */
	si->lmCustomWidth = lmCustomSize;
	si->lmCustomHeight = lmCustomSize;

	/* return to sender */
	return si;
}