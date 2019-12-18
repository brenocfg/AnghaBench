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
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  ALOGI (char*,char const*,char const*) ; 
 scalar_t__ glGetString (int /*<<< orphan*/ ) ; 

void IJK_GLES2_printString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    ALOGI("[GLES2] %s = %s\n", name, v);
}