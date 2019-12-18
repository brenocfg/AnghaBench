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
 int /*<<< orphan*/  QGL_1_1_FIXED_FUNCTION_PROCS ; 
 int /*<<< orphan*/  QGL_1_1_PROCS ; 
 int /*<<< orphan*/  QGL_1_3_PROCS ; 
 int /*<<< orphan*/  QGL_1_5_PROCS ; 
 int /*<<< orphan*/  QGL_2_0_PROCS ; 
 int /*<<< orphan*/  QGL_3_0_PROCS ; 
 int /*<<< orphan*/  QGL_ARB_framebuffer_object_PROCS ; 
 int /*<<< orphan*/  QGL_ARB_occlusion_query_PROCS ; 
 int /*<<< orphan*/  QGL_ARB_vertex_array_object_PROCS ; 
 int /*<<< orphan*/  QGL_DESKTOP_1_1_FIXED_FUNCTION_PROCS ; 
 int /*<<< orphan*/  QGL_DESKTOP_1_1_PROCS ; 
 int /*<<< orphan*/  QGL_ES_1_1_FIXED_FUNCTION_PROCS ; 
 int /*<<< orphan*/  QGL_ES_1_1_PROCS ; 
 int /*<<< orphan*/  QGL_EXT_direct_state_access_PROCS ; 
 int /*<<< orphan*/ * qglActiveTextureARB ; 
 int /*<<< orphan*/ * qglClientActiveTextureARB ; 
 int /*<<< orphan*/ * qglLockArraysEXT ; 
 scalar_t__ qglMajorVersion ; 
 scalar_t__ qglMinorVersion ; 
 int /*<<< orphan*/ * qglMultiTexCoord2fARB ; 
 int /*<<< orphan*/ * qglUnlockArraysEXT ; 
 scalar_t__ qglesMajorVersion ; 
 scalar_t__ qglesMinorVersion ; 

__attribute__((used)) static void GLimp_ClearProcAddresses( void ) {
#define GLE( ret, name, ... ) qgl##name = NULL;

	qglMajorVersion = 0;
	qglMinorVersion = 0;
	qglesMajorVersion = 0;
	qglesMinorVersion = 0;

	QGL_1_1_PROCS;
	QGL_1_1_FIXED_FUNCTION_PROCS;
	QGL_DESKTOP_1_1_PROCS;
	QGL_DESKTOP_1_1_FIXED_FUNCTION_PROCS;
	QGL_ES_1_1_PROCS;
	QGL_ES_1_1_FIXED_FUNCTION_PROCS;
	QGL_1_3_PROCS;
	QGL_1_5_PROCS;
	QGL_2_0_PROCS;
	QGL_3_0_PROCS;
	QGL_ARB_occlusion_query_PROCS;
	QGL_ARB_framebuffer_object_PROCS;
	QGL_ARB_vertex_array_object_PROCS;
	QGL_EXT_direct_state_access_PROCS;

	qglActiveTextureARB = NULL;
	qglClientActiveTextureARB = NULL;
	qglMultiTexCoord2fARB = NULL;

	qglLockArraysEXT = NULL;
	qglUnlockArraysEXT = NULL;

#undef GLE
}