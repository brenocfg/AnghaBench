#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  image; } ;
typedef  TYPE_3__ cubemap_t ;
struct TYPE_22__ {void* finishCalled; } ;
struct TYPE_21__ {scalar_t__ integer; } ;
struct TYPE_20__ {int integer; } ;
struct TYPE_19__ {scalar_t__ integer; } ;
struct TYPE_18__ {int integer; } ;
struct TYPE_17__ {int /*<<< orphan*/ * renderCubeFbo; TYPE_3__* cubemaps; int /*<<< orphan*/ * renderFbo; } ;
struct TYPE_15__ {size_t targetFboCubemapIndex; scalar_t__ isPortal; int /*<<< orphan*/ * targetFbo; int /*<<< orphan*/  targetFboLayer; } ;
struct TYPE_14__ {int rdflags; } ;
struct TYPE_13__ {TYPE_2__ viewParms; void* skyRenderedThisView; void* isHyperspace; TYPE_1__ refdef; scalar_t__ framePostProcessed; void* projection2D; } ;
struct TYPE_12__ {scalar_t__ framebufferObject; } ;
typedef  int /*<<< orphan*/  FBO_t ;

/* Variables and functions */
 int /*<<< orphan*/  FBO_AttachImage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FBO_Bind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GLS_DEFAULT ; 
 int /*<<< orphan*/  GL_COLOR_ATTACHMENT0_EXT ; 
 int GL_COLOR_BUFFER_BIT ; 
 int GL_DEPTH_BUFFER_BIT ; 
 int GL_STENCIL_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_SetModelviewMatrix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_State (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_Hyperspace () ; 
 int RDF_HYPERSPACE ; 
 int RDF_NOWORLDMODEL ; 
 int /*<<< orphan*/  SetViewportAndScissor () ; 
 TYPE_11__ backEnd ; 
 TYPE_10__ glRefConfig ; 
 TYPE_9__ glState ; 
 void* qfalse ; 
 int /*<<< orphan*/  qglClear (int) ; 
 int /*<<< orphan*/  qglFinish () ; 
 void* qtrue ; 
 TYPE_8__* r_fastsky ; 
 TYPE_7__* r_finish ; 
 TYPE_6__* r_measureOverdraw ; 
 TYPE_5__* r_shadows ; 
 int /*<<< orphan*/  s_flipMatrix ; 
 TYPE_4__ tr ; 

void RB_BeginDrawingView (void) {
	int clearBits = 0;

	// sync with gl if needed
	if ( r_finish->integer == 1 && !glState.finishCalled ) {
		qglFinish ();
		glState.finishCalled = qtrue;
	}
	if ( r_finish->integer == 0 ) {
		glState.finishCalled = qtrue;
	}

	// we will need to change the projection matrix before drawing
	// 2D images again
	backEnd.projection2D = qfalse;

	if (glRefConfig.framebufferObject)
	{
		FBO_t *fbo = backEnd.viewParms.targetFbo;

		// FIXME: HUGE HACK: render to the screen fbo if we've already postprocessed the frame and aren't drawing more world
		// drawing more world check is in case of double renders, such as skyportals
		if (fbo == NULL && !(backEnd.framePostProcessed && (backEnd.refdef.rdflags & RDF_NOWORLDMODEL)))
			fbo = tr.renderFbo;

		if (tr.renderCubeFbo && fbo == tr.renderCubeFbo)
		{
			cubemap_t *cubemap = &tr.cubemaps[backEnd.viewParms.targetFboCubemapIndex];
			FBO_AttachImage(fbo, cubemap->image, GL_COLOR_ATTACHMENT0_EXT, backEnd.viewParms.targetFboLayer);
		}

		FBO_Bind(fbo);
	}

	//
	// set the modelview matrix for the viewer
	//
	SetViewportAndScissor();

	// ensures that depth writes are enabled for the depth clear
	GL_State( GLS_DEFAULT );
	// clear relevant buffers
	clearBits = GL_DEPTH_BUFFER_BIT;

	if ( r_measureOverdraw->integer || r_shadows->integer == 2 )
	{
		clearBits |= GL_STENCIL_BUFFER_BIT;
	}
	if ( r_fastsky->integer && !( backEnd.refdef.rdflags & RDF_NOWORLDMODEL ) )
	{
		clearBits |= GL_COLOR_BUFFER_BIT;	// FIXME: only if sky shaders have been used
	}

	// clear to black for cube maps
	if (tr.renderCubeFbo && backEnd.viewParms.targetFbo == tr.renderCubeFbo)
	{
		clearBits |= GL_COLOR_BUFFER_BIT;
	}

	qglClear( clearBits );

	if ( ( backEnd.refdef.rdflags & RDF_HYPERSPACE ) )
	{
		RB_Hyperspace();
		return;
	}
	else
	{
		backEnd.isHyperspace = qfalse;
	}

	// we will only draw a sun if there was sky rendered in this view
	backEnd.skyRenderedThisView = qfalse;

	// clip to the plane of the portal
	if ( backEnd.viewParms.isPortal ) {
#if 0
		float	plane[4];
		GLdouble	plane2[4];

		plane[0] = backEnd.viewParms.portalPlane.normal[0];
		plane[1] = backEnd.viewParms.portalPlane.normal[1];
		plane[2] = backEnd.viewParms.portalPlane.normal[2];
		plane[3] = backEnd.viewParms.portalPlane.dist;

		plane2[0] = DotProduct (backEnd.viewParms.or.axis[0], plane);
		plane2[1] = DotProduct (backEnd.viewParms.or.axis[1], plane);
		plane2[2] = DotProduct (backEnd.viewParms.or.axis[2], plane);
		plane2[3] = DotProduct (plane, backEnd.viewParms.or.origin) - plane[3];
#endif
		GL_SetModelviewMatrix( s_flipMatrix );
	}
}