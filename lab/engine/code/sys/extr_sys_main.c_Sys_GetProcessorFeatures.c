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
typedef  int /*<<< orphan*/  cpuFeatures_t ;

/* Variables and functions */
 int /*<<< orphan*/  CF_3DNOW ; 
 int /*<<< orphan*/  CF_ALTIVEC ; 
 int /*<<< orphan*/  CF_MMX ; 
 int /*<<< orphan*/  CF_RDTSC ; 
 int /*<<< orphan*/  CF_SSE ; 
 int /*<<< orphan*/  CF_SSE2 ; 
 scalar_t__ SDL_Has3DNow () ; 
 scalar_t__ SDL_HasAltiVec () ; 
 scalar_t__ SDL_HasMMX () ; 
 scalar_t__ SDL_HasRDTSC () ; 
 scalar_t__ SDL_HasSSE () ; 
 scalar_t__ SDL_HasSSE2 () ; 

cpuFeatures_t Sys_GetProcessorFeatures( void )
{
	cpuFeatures_t features = 0;

#ifndef DEDICATED
	if( SDL_HasRDTSC( ) )      features |= CF_RDTSC;
	if( SDL_Has3DNow( ) )      features |= CF_3DNOW;
	if( SDL_HasMMX( ) )        features |= CF_MMX;
	if( SDL_HasSSE( ) )        features |= CF_SSE;
	if( SDL_HasSSE2( ) )       features |= CF_SSE2;
	if( SDL_HasAltiVec( ) )    features |= CF_ALTIVEC;
#endif

	return features;
}