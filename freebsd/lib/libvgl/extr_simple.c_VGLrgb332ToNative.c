#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u_long ;
typedef  int byte ;

/* Variables and functions */
 int /*<<< orphan*/  VGLrgbToNative (int,int,int) ; 

u_long
VGLrgb332ToNative(byte c)
{
  uint16_t r, g, b;

  /* 3:3:2 to 16:16:16 */
  r = ((c & 0xe0) >> 5) * 0xffff / 7;
  g = ((c & 0x1c) >> 2) * 0xffff / 7;
  b = ((c & 0x03) >> 0) * 0xffff / 3;

  return VGLrgbToNative(r, g, b);
}