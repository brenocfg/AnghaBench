#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_8__ {int buffWidth; int buffHeight; } ;
struct TYPE_7__ {int value; } ;
struct TYPE_6__ {int value; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* Cvar_Set ) (char*,char*) ;} ;
typedef  int /*<<< orphan*/  GLubyte ;

/* Variables and functions */
 int /*<<< orphan*/  GLimp_CommonPostInit () ; 
 int /*<<< orphan*/  GLimp_CommonPreInit () ; 
 int /*<<< orphan*/  OSMESA_RGBA ; 
 int /*<<< orphan*/  OSMesaCreateContextExt (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Sys_Error (char*) ; 
 int /*<<< orphan*/  calloc (int,int) ; 
 TYPE_4__ glConfig ; 
 int /*<<< orphan*/  osmesa_ctx ; 
 int /*<<< orphan*/  osmesa_frame_buffer ; 
 TYPE_3__* r_colorbits ; 
 TYPE_2__* r_depthbits ; 
 TYPE_1__ ri ; 
 int /*<<< orphan*/  stub1 (char*,char*) ; 

void GLimp_Init(qboolean coreContext) {
  r_colorbits->value = 16;
  r_depthbits->value = 24;
  GLimp_CommonPreInit();
  /* Create an RGBA-mode context */
  osmesa_ctx =
      OSMesaCreateContextExt(OSMESA_RGBA, r_depthbits->value, 0, 0, NULL);
  if (!osmesa_ctx) {
    Sys_Error("OSMesaCreateContext failed!");
  }

  /* Allocate the image buffer */
  osmesa_frame_buffer =
      calloc(glConfig.buffWidth * glConfig.buffHeight * 4, sizeof(GLubyte));
  if (!osmesa_frame_buffer) {
    Sys_Error("Alloc image buffer failed!");
  }

  // Force draw buffer to GL_FRONT, as OSMesa doesn't have a back buffer to
  // render to.
  ri.Cvar_Set("r_drawBuffer", "GL_FRONT");

  GLimp_CommonPostInit();
}