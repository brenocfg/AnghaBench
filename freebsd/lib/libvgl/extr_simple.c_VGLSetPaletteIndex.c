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
typedef  size_t byte ;
struct TYPE_2__ {scalar_t__ vi_mem_model; } ;

/* Variables and functions */
 int /*<<< orphan*/  VGLCheckSwitch () ; 
 TYPE_1__ VGLModeInfo ; 
 size_t* VGLSavePaletteBlue ; 
 size_t* VGLSavePaletteGreen ; 
 size_t* VGLSavePaletteRed ; 
 scalar_t__ V_INFO_MM_DIRECT ; 
 int /*<<< orphan*/  inb (int) ; 
 int /*<<< orphan*/  outb (int,int) ; 

void
VGLSetPaletteIndex(byte color, byte red, byte green, byte blue)
{
  if (VGLModeInfo.vi_mem_model == V_INFO_MM_DIRECT)
    return;
  VGLSavePaletteRed[color] = red;
  VGLSavePaletteGreen[color] = green;
  VGLSavePaletteBlue[color] = blue;
  VGLCheckSwitch();
  outb(0x3C6, 0xFF);
  inb(0x3DA);
  outb(0x3C8, color); 
  outb(0x3C9, red); outb(0x3C9, green); outb(0x3C9, blue);
  inb(0x3DA);
  outb(0x3C0, 0x20);
}