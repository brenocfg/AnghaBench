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
typedef  int uint16_t ;
typedef  int u_long ;
struct TYPE_2__ {int* vi_pixel_fsizes; } ;

/* Variables and functions */
 TYPE_1__ VGLModeInfo ; 

__attribute__((used)) static inline u_long
VGLrgbToNative(uint16_t r, uint16_t g, uint16_t b)
{
  int nr, ng, nb;

  nr = VGLModeInfo.vi_pixel_fsizes[2];
  ng = VGLModeInfo.vi_pixel_fsizes[1];
  nb = VGLModeInfo.vi_pixel_fsizes[0];
  return (r >> (16 - nr) << (ng + nb)) | (g >> (16 - ng) << nb) |
	 (b >> (16 - nb) << 0);
}