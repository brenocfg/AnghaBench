#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ stereoEnabled; } ;
struct TYPE_10__ {TYPE_1__ glconfig; } ;
struct TYPE_9__ {scalar_t__ integer; } ;
struct TYPE_8__ {scalar_t__ integer; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* EndFrame ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int Cvar_VariableIntegerValue (char*) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 int /*<<< orphan*/  SCR_DrawScreenField (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STEREO_CENTER ; 
 int /*<<< orphan*/  STEREO_LEFT ; 
 int /*<<< orphan*/  STEREO_RIGHT ; 
 TYPE_5__ cls ; 
 TYPE_4__* com_dedicated ; 
 TYPE_3__* com_speeds ; 
 TYPE_2__ re ; 
 int /*<<< orphan*/  renderOrigin ; 
 int /*<<< orphan*/  scr_initialized ; 
 int /*<<< orphan*/  skipRendering ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time_backend ; 
 int /*<<< orphan*/  time_frontend ; 
 scalar_t__ uivm ; 

void SCR_UpdateScreen( void ) {
	static int	recursive;

	if ( !scr_initialized ) {
		return;				// not initialized yet
	}

	if ( ++recursive > 2 ) {
		Com_Error( ERR_FATAL, "SCR_UpdateScreen: recursively called" );
	}
	recursive = 1;

	// If there is no VM, there are also no rendering commands issued. Stop the renderer in
	// that case.
	if( uivm || com_dedicated->integer )
	{
		// XXX
		int in_anaglyphMode = Cvar_VariableIntegerValue("r_anaglyphMode");
		// if running in stereo, we need to draw the frame twice
		if ( cls.glconfig.stereoEnabled || in_anaglyphMode) {
			SCR_DrawScreenField( STEREO_LEFT, renderOrigin, skipRendering );
			SCR_DrawScreenField( STEREO_RIGHT, renderOrigin, skipRendering );
		} else {
			SCR_DrawScreenField( STEREO_CENTER, renderOrigin, skipRendering );
		}

		if ( !skipRendering ) {
			if ( com_speeds->integer ) {
				re.EndFrame( &time_frontend, &time_backend );
			} else {
				re.EndFrame( NULL, NULL );
			}
		}
	}

	recursive = 0;
}