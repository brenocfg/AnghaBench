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
typedef  scalar_t__ GLenum ;

/* Variables and functions */
 scalar_t__ GL_NO_ERROR ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__,char const*) ; 
 scalar_t__ glad_glGetError () ; 
 int /*<<< orphan*/  stderr ; 

void _post_call_callback_default(const char *name, void *funcptr, int len_args, ...) {
    GLenum error_code;
    (void) funcptr;
    (void) len_args;
    error_code = glad_glGetError();
    if (error_code != GL_NO_ERROR) {
        fprintf(stderr, "ERROR %d in %s\n", error_code, name);
    }
}