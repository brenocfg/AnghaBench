#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  buttons; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_8__ {int /*<<< orphan*/  signal; } ;
struct TYPE_10__ {TYPE_2__ data; TYPE_1__ mode; } ;
struct mouse_info {TYPE_3__ u; int /*<<< orphan*/  operation; } ;
struct TYPE_11__ {int VXsize; int VYsize; int* Bitmap; } ;
typedef  TYPE_4__ VGLBitmap ;
struct TYPE_12__ {int vi_mem_model; scalar_t__ vi_mode; } ;

/* Variables and functions */
 int BORDER ; 
 int /*<<< orphan*/  CONS_MOUSECTL ; 
 int INTERIOR ; 
 int /*<<< orphan*/  MOUSE_GETINFO ; 
 int /*<<< orphan*/  MOUSE_MODE ; 
 scalar_t__ M_BG640x480 ; 
 int /*<<< orphan*/  SIGUSR2 ; 
 TYPE_7__ VGLModeInfo ; 
 int /*<<< orphan*/  VGLMouseAction ; 
 int /*<<< orphan*/  VGLMouseButtons ; 
 TYPE_4__ VGLMouseLargeOrMask ; 
 int /*<<< orphan*/  VGLMouseMode (int) ; 
 int /*<<< orphan*/  VGLMouseSetStdImage () ; 
 TYPE_4__ VGLMouseSmallOrMask ; 
 int /*<<< orphan*/  VGLMouseXpos ; 
 int /*<<< orphan*/  VGLMouseYpos ; 
#define  V_INFO_MM_PACKED 130 
#define  V_INFO_MM_PLANAR 129 
#define  V_INFO_MM_VGAX 128 
 int /*<<< orphan*/ * getenv (char*) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mouse_info*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strtoul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
VGLMouseInit(int mode)
{
  struct mouse_info mouseinfo;
  VGLBitmap *ormask;
  int andmask, border, error, i, interior;

  switch (VGLModeInfo.vi_mem_model) {
  case V_INFO_MM_PACKED:
  case V_INFO_MM_PLANAR:
    andmask = 0x0f;
    border = 0x0f;
    interior = 0x04;
    break;
  case V_INFO_MM_VGAX:
    andmask = 0x3f;
    border = 0x3f;
    interior = 0x24;
    break;
  default:
    andmask = 0xff;
    border = BORDER;
    interior = INTERIOR;
    break;
  }
  if (VGLModeInfo.vi_mode == M_BG640x480)
    border = 0;		/* XXX (palette makes 0x04 look like 0x0f) */
  if (getenv("VGLMOUSEBORDERCOLOR") != NULL)
    border = strtoul(getenv("VGLMOUSEBORDERCOLOR"), NULL, 0);
  if (getenv("VGLMOUSEINTERIORCOLOR") != NULL)
    interior = strtoul(getenv("VGLMOUSEINTERIORCOLOR"), NULL, 0);
  ormask = &VGLMouseLargeOrMask;
  for (i = 0; i < ormask->VXsize * ormask->VYsize; i++)
    ormask->Bitmap[i] = ormask->Bitmap[i] == BORDER ?  border :
                        ormask->Bitmap[i] == INTERIOR ? interior : 0;
  ormask = &VGLMouseSmallOrMask;
  for (i = 0; i < ormask->VXsize * ormask->VYsize; i++)
    ormask->Bitmap[i] = ormask->Bitmap[i] == BORDER ?  border :
                        ormask->Bitmap[i] == INTERIOR ? interior : 0;
  VGLMouseSetStdImage();
  mouseinfo.operation = MOUSE_MODE;
  mouseinfo.u.mode.signal = SIGUSR2;
  if ((error = ioctl(0, CONS_MOUSECTL, &mouseinfo)))
    return error;
  signal(SIGUSR2, VGLMouseAction);
  mouseinfo.operation = MOUSE_GETINFO;
  ioctl(0, CONS_MOUSECTL, &mouseinfo);
  VGLMouseXpos = mouseinfo.u.data.x;
  VGLMouseYpos = mouseinfo.u.data.y;
  VGLMouseButtons = mouseinfo.u.data.buttons;
  VGLMouseMode(mode);
  return 0;
}