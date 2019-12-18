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
 int VGLBlank ; 
 int /*<<< orphan*/  VGLCheckSwitch () ; 
 TYPE_1__ VGLModeInfo ; 
 scalar_t__ V_INFO_MM_DIRECT ; 
 int inb (int) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int) ; 

void
VGLBlankDisplay(int blank)
{
  byte val;

  if (VGLModeInfo.vi_mem_model == V_INFO_MM_DIRECT && ioctl(0, KDENABIO, 0))
    return;
  VGLCheckSwitch();
  outb(0x3C4, 0x01); val = inb(0x3C5); outb(0x3C4, 0x01);
  outb(0x3C5, ((blank) ? (val |= 0x20) : (val &= 0xDF)));
  VGLBlank = blank;
  if (VGLModeInfo.vi_mem_model == V_INFO_MM_DIRECT)
    ioctl(0, KDDISABIO, 0);
}