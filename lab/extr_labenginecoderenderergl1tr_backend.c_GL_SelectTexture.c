#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int currenttmu; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* Error ) (int /*<<< orphan*/ ,char*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_DROP ; 
 int /*<<< orphan*/  GL_TEXTURE0_ARB ; 
 int /*<<< orphan*/  GL_TEXTURE1_ARB ; 
 int /*<<< orphan*/  GLimp_LogComment (char*) ; 
 TYPE_2__ glState ; 
 int /*<<< orphan*/  qglActiveTextureARB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglClientActiveTextureARB (int /*<<< orphan*/ ) ; 
 TYPE_1__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 

void GL_SelectTexture( int unit )
{
	if ( glState.currenttmu == unit )
	{
		return;
	}

	if ( unit == 0 )
	{
		qglActiveTextureARB( GL_TEXTURE0_ARB );
		GLimp_LogComment( "glActiveTextureARB( GL_TEXTURE0_ARB )\n" );
		qglClientActiveTextureARB( GL_TEXTURE0_ARB );
		GLimp_LogComment( "glClientActiveTextureARB( GL_TEXTURE0_ARB )\n" );
	}
	else if ( unit == 1 )
	{
		qglActiveTextureARB( GL_TEXTURE1_ARB );
		GLimp_LogComment( "glActiveTextureARB( GL_TEXTURE1_ARB )\n" );
		qglClientActiveTextureARB( GL_TEXTURE1_ARB );
		GLimp_LogComment( "glClientActiveTextureARB( GL_TEXTURE1_ARB )\n" );
	} else {
		ri.Error( ERR_DROP, "GL_SelectTexture: unit = %i", unit );
	}

	glState.currenttmu = unit;
}