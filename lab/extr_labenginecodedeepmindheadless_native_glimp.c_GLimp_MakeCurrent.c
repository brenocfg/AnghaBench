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

/* Variables and functions */
 int /*<<< orphan*/  Sys_Error (char*) ; 
 int /*<<< orphan*/  glXMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glx_context ; 
 int /*<<< orphan*/  glx_display ; 
 int /*<<< orphan*/  glx_pbuffer ; 

void GLimp_MakeCurrent(void) {
  if (!glXMakeCurrent(glx_display, glx_pbuffer, glx_context)) {
    Sys_Error("GLimp_MakeCurrent - Failed!");
  }
}