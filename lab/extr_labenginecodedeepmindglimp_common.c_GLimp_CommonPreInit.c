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
struct TYPE_4__ {int /*<<< orphan*/  windowAspect; int /*<<< orphan*/  buffHeight; int /*<<< orphan*/  buffWidth; int /*<<< orphan*/  vidHeight; int /*<<< orphan*/  vidWidth; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* Cvar_Get ) (char*,char*,int) ;} ;

/* Variables and functions */
 int CVAR_ARCHIVE ; 
 int CVAR_LATCH ; 
 int CVAR_ROM ; 
 int /*<<< orphan*/  R_GetModeInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_2__ glConfig ; 
 int /*<<< orphan*/  r_allowResize ; 
 int /*<<< orphan*/  r_centerWindow ; 
 int /*<<< orphan*/  r_motionblur ; 
 int /*<<< orphan*/  r_sdlDriver ; 
 int /*<<< orphan*/  r_tvConsoleMode ; 
 int /*<<< orphan*/  r_tvMode ; 
 int /*<<< orphan*/  r_tvModeAspect ; 
 TYPE_1__ ri ; 
 int /*<<< orphan*/  stub1 (char*,char*,int) ; 
 int /*<<< orphan*/  stub2 (char*,char*,int) ; 
 int /*<<< orphan*/  stub3 (char*,char*,int) ; 
 int /*<<< orphan*/  stub4 (char*,char*,int) ; 
 int /*<<< orphan*/  stub5 (char*,char*,int) ; 
 int /*<<< orphan*/  stub6 (char*,char*,int) ; 
 int /*<<< orphan*/  stub7 (char*,char*,int) ; 

void GLimp_CommonPreInit(void) {
  r_sdlDriver = ri.Cvar_Get("r_sdlDriver", "", CVAR_ROM);
  r_allowResize = ri.Cvar_Get("r_allowResize", "0", CVAR_ARCHIVE | CVAR_LATCH);
  r_centerWindow =
      ri.Cvar_Get("r_centerWindow", "0", CVAR_ARCHIVE | CVAR_LATCH);
  r_tvMode = ri.Cvar_Get("r_tvMode", "-1", CVAR_LATCH | CVAR_ARCHIVE);
  r_tvModeAspect =
      ri.Cvar_Get("r_tvModeAspect", "0", CVAR_LATCH | CVAR_ARCHIVE);
  r_tvConsoleMode =
      ri.Cvar_Get("r_tvConsoleMode", "0", CVAR_LATCH | CVAR_ARCHIVE);
  r_motionblur = ri.Cvar_Get("r_motionblur", "0", CVAR_ARCHIVE | CVAR_LATCH);
  // Ignore r_tvMode.
  R_GetModeInfo(&glConfig.vidWidth, &glConfig.vidHeight, &glConfig.buffWidth,
                &glConfig.buffHeight, &glConfig.windowAspect, -1);
}