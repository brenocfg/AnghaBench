#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_5__ {int /*<<< orphan*/  integer; } ;
typedef  TYPE_1__ cvar_t ;
struct TYPE_7__ {int /*<<< orphan*/  buffHeight; int /*<<< orphan*/  buffWidth; } ;
struct TYPE_6__ {TYPE_1__* (* Cvar_Get ) (char*,char*,int) ;} ;
typedef  int /*<<< orphan*/  EGLint ;
typedef  int /*<<< orphan*/  EGLConfig ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_EGL_SUCCESS (int /*<<< orphan*/ ) ; 
 int CVAR_ARCHIVE ; 
 int CVAR_LATCH ; 
 scalar_t__ CreateInitializedEGLDisplayAtIndex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EGL_HEIGHT ; 
 int /*<<< orphan*/  EGL_NONE ; 
 int /*<<< orphan*/  EGL_NO_CONTEXT ; 
 scalar_t__ EGL_NO_DISPLAY ; 
 int /*<<< orphan*/  EGL_OPENGL_API ; 
 int /*<<< orphan*/  EGL_WIDTH ; 
 int /*<<< orphan*/  GLimp_CommonPostInit () ; 
 int /*<<< orphan*/  GLimp_CommonPreInit () ; 
 int /*<<< orphan*/  Sys_Error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglBindAPI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglChooseConfig (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eglCreateContext (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eglCreatePbufferSurface (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  egl_context ; 
 scalar_t__ egl_display ; 
 int /*<<< orphan*/  egl_surface ; 
 TYPE_4__ glConfig ; 
 int /*<<< orphan*/  kConfigAttribs ; 
 TYPE_3__ ri ; 
 TYPE_1__* stub1 (char*,char*,int) ; 

void GLimp_Init(qboolean coreContext) {
  GLimp_CommonPreInit();

  cvar_t* r_gpu_device_index =
      ri.Cvar_Get("r_gpuDeviceIndex", "0", CVAR_ARCHIVE | CVAR_LATCH);

  egl_display = CreateInitializedEGLDisplayAtIndex(r_gpu_device_index->integer);
  if (egl_display == EGL_NO_DISPLAY) {
    Sys_Error("Failed to create EGL display for device index %d!\n",
              r_gpu_device_index->integer);
    return;
  }

  EGLint num_configs;
  EGLConfig egl_config;
  CHECK_EGL_SUCCESS(eglChooseConfig(egl_display, kConfigAttribs, &egl_config, 1,
                                    &num_configs));

  EGLint pbuffer_attribs[] = {
      EGL_WIDTH,  glConfig.buffWidth,   //
      EGL_HEIGHT, glConfig.buffHeight,  //
      EGL_NONE,
  };

  CHECK_EGL_SUCCESS(egl_surface = eglCreatePbufferSurface(
                        egl_display, egl_config, pbuffer_attribs));

  CHECK_EGL_SUCCESS(eglBindAPI(EGL_OPENGL_API));

  CHECK_EGL_SUCCESS(egl_context = eglCreateContext(egl_display, egl_config,
                                                   EGL_NO_CONTEXT, NULL));

  GLimp_CommonPostInit();
}