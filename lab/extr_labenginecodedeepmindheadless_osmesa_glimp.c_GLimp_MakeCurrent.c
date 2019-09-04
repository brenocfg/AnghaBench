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
struct TYPE_2__ {int /*<<< orphan*/  buffHeight; int /*<<< orphan*/  buffWidth; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int /*<<< orphan*/  OSMesaMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sys_Error (char*) ; 
 TYPE_1__ glConfig ; 
 int /*<<< orphan*/  osmesa_ctx ; 
 int /*<<< orphan*/  osmesa_frame_buffer ; 

void GLimp_MakeCurrent(void) {
  if (!OSMesaMakeCurrent(osmesa_ctx, osmesa_frame_buffer, GL_UNSIGNED_BYTE,
                         glConfig.buffWidth, glConfig.buffHeight)) {
    Sys_Error("GLimp_MakeCurrent - Failed!");
  }
}