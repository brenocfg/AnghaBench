#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* backend_ctx; } ;
typedef  TYPE_1__ hashcat_ctx_t ;
typedef  int /*<<< orphan*/  dllname ;
struct TYPE_8__ {scalar_t__ nvrtc; } ;
typedef  TYPE_2__ backend_ctx_t ;
struct TYPE_9__ {int /*<<< orphan*/ * lib; } ;
typedef  TYPE_3__ NVRTC_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  HC_LOAD_FUNC (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NVRTC ; 
 int /*<<< orphan*/  NVRTC_NVRTCADDNAMEEXPRESSION ; 
 int /*<<< orphan*/  NVRTC_NVRTCCOMPILEPROGRAM ; 
 int /*<<< orphan*/  NVRTC_NVRTCCREATEPROGRAM ; 
 int /*<<< orphan*/  NVRTC_NVRTCDESTROYPROGRAM ; 
 int /*<<< orphan*/  NVRTC_NVRTCGETERRORSTRING ; 
 int /*<<< orphan*/  NVRTC_NVRTCGETLOWEREDNAME ; 
 int /*<<< orphan*/  NVRTC_NVRTCGETPROGRAMLOG ; 
 int /*<<< orphan*/  NVRTC_NVRTCGETPROGRAMLOGSIZE ; 
 int /*<<< orphan*/  NVRTC_NVRTCGETPTX ; 
 int /*<<< orphan*/  NVRTC_NVRTCGETPTXSIZE ; 
 int /*<<< orphan*/  NVRTC_NVRTCVERSION ; 
 void* hc_dlopen (char*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvrtcAddNameExpression ; 
 int /*<<< orphan*/  nvrtcCompileProgram ; 
 int /*<<< orphan*/  nvrtcCreateProgram ; 
 int /*<<< orphan*/  nvrtcDestroyProgram ; 
 int /*<<< orphan*/  nvrtcGetErrorString ; 
 int /*<<< orphan*/  nvrtcGetLoweredName ; 
 int /*<<< orphan*/  nvrtcGetPTX ; 
 int /*<<< orphan*/  nvrtcGetPTXSize ; 
 int /*<<< orphan*/  nvrtcGetProgramLog ; 
 int /*<<< orphan*/  nvrtcGetProgramLogSize ; 
 int /*<<< orphan*/  nvrtcVersion ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 

int nvrtc_init (hashcat_ctx_t *hashcat_ctx)
{
  backend_ctx_t *backend_ctx = hashcat_ctx->backend_ctx;

  NVRTC_PTR *nvrtc = (NVRTC_PTR *) backend_ctx->nvrtc;

  memset (nvrtc, 0, sizeof (NVRTC_PTR));

  #if   defined (_WIN)
  nvrtc->lib = hc_dlopen ("nvrtc.dll");

  if (nvrtc->lib == NULL)
  {
    // super annoying: nvidia is using the CUDA version in nvrtc???.dll filename!
    // however, the cuda version string comes from nvcuda.dll which is from nvidia driver, but
    // the driver version and the installed CUDA toolkit version can be different, so it cannot be used as a reference.
    // brute force to the rescue

    char dllname[100];

    for (int major = 20; major >= 10; major--) // older than 3.x do not ship _v2 functions anyway
                                               // older than 7.x does not support sm 5.x
                                               // older than 8.x does not have documentation archive online, no way to check if nvrtc support whatever we need
                                               // older than 10.x is just a theoretical limit since we define 10.1 as the minimum required version
    {
      for (int minor = 20; minor >= 0; minor--)
      {
        snprintf (dllname, sizeof (dllname), "nvrtc64_%d%d.dll", major, minor);

        nvrtc->lib = hc_dlopen (dllname);

        if (nvrtc->lib) break;

        snprintf (dllname, sizeof (dllname), "nvrtc64_%d%d_0.dll", major, minor);

        nvrtc->lib = hc_dlopen (dllname);

        if (nvrtc->lib) break;
      }

      if (nvrtc->lib) break;
    }
  }
  #elif defined (__APPLE__)
  nvrtc->lib = hc_dlopen ("nvrtc.dylib");
  #elif defined (__CYGWIN__)
  nvrtc->lib = hc_dlopen ("nvrtc.dll");
  #else
  nvrtc->lib = hc_dlopen ("libnvrtc.so");

  if (nvrtc->lib == NULL) nvrtc->lib = hc_dlopen ("libnvrtc.so.1");
  #endif

  if (nvrtc->lib == NULL) return -1;

  HC_LOAD_FUNC (nvrtc, nvrtcAddNameExpression,  NVRTC_NVRTCADDNAMEEXPRESSION, NVRTC, 1);
  HC_LOAD_FUNC (nvrtc, nvrtcCompileProgram,     NVRTC_NVRTCCOMPILEPROGRAM,    NVRTC, 1);
  HC_LOAD_FUNC (nvrtc, nvrtcCreateProgram,      NVRTC_NVRTCCREATEPROGRAM,     NVRTC, 1);
  HC_LOAD_FUNC (nvrtc, nvrtcDestroyProgram,     NVRTC_NVRTCDESTROYPROGRAM,    NVRTC, 1);
  HC_LOAD_FUNC (nvrtc, nvrtcGetLoweredName,     NVRTC_NVRTCGETLOWEREDNAME,    NVRTC, 1);
  HC_LOAD_FUNC (nvrtc, nvrtcGetPTX,             NVRTC_NVRTCGETPTX,            NVRTC, 1);
  HC_LOAD_FUNC (nvrtc, nvrtcGetPTXSize,         NVRTC_NVRTCGETPTXSIZE,        NVRTC, 1);
  HC_LOAD_FUNC (nvrtc, nvrtcGetProgramLog,      NVRTC_NVRTCGETPROGRAMLOG,     NVRTC, 1);
  HC_LOAD_FUNC (nvrtc, nvrtcGetProgramLogSize,  NVRTC_NVRTCGETPROGRAMLOGSIZE, NVRTC, 1);
  HC_LOAD_FUNC (nvrtc, nvrtcGetErrorString,     NVRTC_NVRTCGETERRORSTRING,    NVRTC, 1);
  HC_LOAD_FUNC (nvrtc, nvrtcVersion,            NVRTC_NVRTCVERSION,           NVRTC, 1);

  return 0;
}