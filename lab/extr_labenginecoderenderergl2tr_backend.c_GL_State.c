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
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {unsigned long glStateBits; unsigned long storedGlState; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* Error ) (int /*<<< orphan*/ ,char*) ;} ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_DROP ; 
 unsigned long GLS_DEPTHFUNC_BITS ; 
 unsigned long GLS_DEPTHFUNC_EQUAL ; 
 unsigned long GLS_DEPTHFUNC_GREATER ; 
 unsigned long GLS_DEPTHMASK_TRUE ; 
 unsigned long GLS_DEPTHTEST_DISABLE ; 
 unsigned long GLS_DSTBLEND_BITS ; 
#define  GLS_DSTBLEND_DST_ALPHA 144 
#define  GLS_DSTBLEND_ONE 143 
#define  GLS_DSTBLEND_ONE_MINUS_DST_ALPHA 142 
#define  GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA 141 
#define  GLS_DSTBLEND_ONE_MINUS_SRC_COLOR 140 
#define  GLS_DSTBLEND_SRC_ALPHA 139 
#define  GLS_DSTBLEND_SRC_COLOR 138 
#define  GLS_DSTBLEND_ZERO 137 
 unsigned long GLS_POLYMODE_LINE ; 
#define  GLS_SRCBLEND_ALPHA_SATURATE 136 
 unsigned long GLS_SRCBLEND_BITS ; 
#define  GLS_SRCBLEND_DST_ALPHA 135 
#define  GLS_SRCBLEND_DST_COLOR 134 
#define  GLS_SRCBLEND_ONE 133 
#define  GLS_SRCBLEND_ONE_MINUS_DST_ALPHA 132 
#define  GLS_SRCBLEND_ONE_MINUS_DST_COLOR 131 
#define  GLS_SRCBLEND_ONE_MINUS_SRC_ALPHA 130 
#define  GLS_SRCBLEND_SRC_ALPHA 129 
#define  GLS_SRCBLEND_ZERO 128 
 int /*<<< orphan*/  GL_BLEND ; 
 int /*<<< orphan*/  GL_DEPTH_TEST ; 
 int /*<<< orphan*/  GL_DST_ALPHA ; 
 int /*<<< orphan*/  GL_DST_COLOR ; 
 int /*<<< orphan*/  GL_EQUAL ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_FILL ; 
 int /*<<< orphan*/  GL_FRONT_AND_BACK ; 
 int /*<<< orphan*/  GL_GREATER ; 
 int /*<<< orphan*/  GL_LEQUAL ; 
 int /*<<< orphan*/  GL_LINE ; 
 int /*<<< orphan*/  GL_ONE ; 
 int /*<<< orphan*/  GL_ONE_MINUS_DST_ALPHA ; 
 int /*<<< orphan*/  GL_ONE_MINUS_DST_COLOR ; 
 int /*<<< orphan*/  GL_ONE_MINUS_SRC_ALPHA ; 
 int /*<<< orphan*/  GL_ONE_MINUS_SRC_COLOR ; 
 int /*<<< orphan*/  GL_SRC_ALPHA ; 
 int /*<<< orphan*/  GL_SRC_ALPHA_SATURATE ; 
 int /*<<< orphan*/  GL_SRC_COLOR ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int /*<<< orphan*/  GL_ZERO ; 
 TYPE_2__ glState ; 
 int /*<<< orphan*/  qglBlendFunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglDepthFunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglDepthMask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglPolygonMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*) ; 

void GL_State( unsigned long stateBits )
{
	unsigned long diff = stateBits ^ glState.glStateBits;

	if ( !diff )
	{
		return;
	}

	//
	// check depthFunc bits
	//
	if ( diff & GLS_DEPTHFUNC_BITS )
	{
		if ( stateBits & GLS_DEPTHFUNC_EQUAL )
		{
			qglDepthFunc( GL_EQUAL );
		}
		else if ( stateBits & GLS_DEPTHFUNC_GREATER)
		{
			qglDepthFunc( GL_GREATER );
		}
		else
		{
			qglDepthFunc( GL_LEQUAL );
		}
	}

	//
	// check blend bits
	//
	if ( diff & ( GLS_SRCBLEND_BITS | GLS_DSTBLEND_BITS ) )
	{
		uint32_t oldState = glState.glStateBits & ( GLS_SRCBLEND_BITS | GLS_DSTBLEND_BITS );
		uint32_t newState = stateBits & ( GLS_SRCBLEND_BITS | GLS_DSTBLEND_BITS );
		uint32_t storedState = glState.storedGlState & ( GLS_SRCBLEND_BITS | GLS_DSTBLEND_BITS );

		if (oldState == 0)
		{
			qglEnable( GL_BLEND );
		}
		else if (newState == 0)
		{
			qglDisable( GL_BLEND );
		}

		if (newState != 0 && storedState != newState)
		{
			GLenum srcFactor = GL_ONE, dstFactor = GL_ONE;

			glState.storedGlState &= ~( GLS_SRCBLEND_BITS | GLS_DSTBLEND_BITS );
			glState.storedGlState |= newState;

			switch ( stateBits & GLS_SRCBLEND_BITS )
			{
			case GLS_SRCBLEND_ZERO:
				srcFactor = GL_ZERO;
				break;
			case GLS_SRCBLEND_ONE:
				srcFactor = GL_ONE;
				break;
			case GLS_SRCBLEND_DST_COLOR:
				srcFactor = GL_DST_COLOR;
				break;
			case GLS_SRCBLEND_ONE_MINUS_DST_COLOR:
				srcFactor = GL_ONE_MINUS_DST_COLOR;
				break;
			case GLS_SRCBLEND_SRC_ALPHA:
				srcFactor = GL_SRC_ALPHA;
				break;
			case GLS_SRCBLEND_ONE_MINUS_SRC_ALPHA:
				srcFactor = GL_ONE_MINUS_SRC_ALPHA;
				break;
			case GLS_SRCBLEND_DST_ALPHA:
				srcFactor = GL_DST_ALPHA;
				break;
			case GLS_SRCBLEND_ONE_MINUS_DST_ALPHA:
				srcFactor = GL_ONE_MINUS_DST_ALPHA;
				break;
			case GLS_SRCBLEND_ALPHA_SATURATE:
				srcFactor = GL_SRC_ALPHA_SATURATE;
				break;
			default:
				ri.Error( ERR_DROP, "GL_State: invalid src blend state bits" );
				break;
			}

			switch ( stateBits & GLS_DSTBLEND_BITS )
			{
			case GLS_DSTBLEND_ZERO:
				dstFactor = GL_ZERO;
				break;
			case GLS_DSTBLEND_ONE:
				dstFactor = GL_ONE;
				break;
			case GLS_DSTBLEND_SRC_COLOR:
				dstFactor = GL_SRC_COLOR;
				break;
			case GLS_DSTBLEND_ONE_MINUS_SRC_COLOR:
				dstFactor = GL_ONE_MINUS_SRC_COLOR;
				break;
			case GLS_DSTBLEND_SRC_ALPHA:
				dstFactor = GL_SRC_ALPHA;
				break;
			case GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA:
				dstFactor = GL_ONE_MINUS_SRC_ALPHA;
				break;
			case GLS_DSTBLEND_DST_ALPHA:
				dstFactor = GL_DST_ALPHA;
				break;
			case GLS_DSTBLEND_ONE_MINUS_DST_ALPHA:
				dstFactor = GL_ONE_MINUS_DST_ALPHA;
				break;
			default:
				ri.Error( ERR_DROP, "GL_State: invalid dst blend state bits" );
				break;
			}

			qglBlendFunc( srcFactor, dstFactor );
		}
	}

	//
	// check depthmask
	//
	if ( diff & GLS_DEPTHMASK_TRUE )
	{
		if ( stateBits & GLS_DEPTHMASK_TRUE )
		{
			qglDepthMask( GL_TRUE );
		}
		else
		{
			qglDepthMask( GL_FALSE );
		}
	}

	//
	// fill/line mode
	//
	if ( diff & GLS_POLYMODE_LINE )
	{
		if ( stateBits & GLS_POLYMODE_LINE )
		{
			qglPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		}
		else
		{
			qglPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		}
	}

	//
	// depthtest
	//
	if ( diff & GLS_DEPTHTEST_DISABLE )
	{
		if ( stateBits & GLS_DEPTHTEST_DISABLE )
		{
			qglDisable( GL_DEPTH_TEST );
		}
		else
		{
			qglEnable( GL_DEPTH_TEST );
		}
	}

	glState.glStateBits = stateBits;
}