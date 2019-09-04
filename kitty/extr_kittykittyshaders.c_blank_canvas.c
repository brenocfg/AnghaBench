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
typedef  float GLfloat ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int OPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  background ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (float,float,float,float) ; 

void
blank_canvas(float background_opacity) {
#define C(shift) (((GLfloat)((OPT(background) >> shift) & 0xFF)) / 255.0f)
        glClearColor(C(16), C(8), C(0), background_opacity);
#undef C
        glClear(GL_COLOR_BUFFER_BIT);
}