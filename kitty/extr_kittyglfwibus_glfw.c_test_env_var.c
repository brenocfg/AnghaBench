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
typedef  int /*<<< orphan*/  GLFWbool ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 char* getenv (char const*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static inline GLFWbool
test_env_var(const char *name, const char *val) {
    const char *q = getenv(name);
    return (q && strcmp(q, val) == 0) ? GLFW_TRUE : GLFW_FALSE;
}