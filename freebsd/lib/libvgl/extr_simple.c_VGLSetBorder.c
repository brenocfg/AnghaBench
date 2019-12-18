#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int byte ;
struct TYPE_2__ {scalar_t__ vi_mem_model; } ;

/* Variables and functions */
 int /*<<< orphan*/  KDDISABIO ; 
 int /*<<< orphan*/  KDENABIO ; 
 int VGLBorderColor ; 
 int /*<<< orphan*/  VGLCheckSwitch () ; 
 TYPE_1__ VGLModeInfo ; 
 scalar_t__ V_INFO_MM_DIRECT ; 
 int /*<<< orphan*/  inb (int) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int) ; 

void
VGLSetBorder(byte color)
{
  if (VGLModeInfo.vi_mem_model == V_INFO_MM_DIRECT && ioctl(0, KDENABIO, 0))
    return;
  VGLCheckSwitch();
  inb(0x3DA);
  outb(0x3C0,0x11); outb(0x3C0, color); 
  inb(0x3DA);
  outb(0x3C0, 0x20);
  VGLBorderColor = color;
  if (VGLModeInfo.vi_mem_model == V_INFO_MM_DIRECT)
    ioctl(0, KDDISABIO, 0);
}