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
typedef  scalar_t__ GLFWbool ;

/* Variables and functions */
 int /*<<< orphan*/  XKB_KEYSYM_CASE_INSENSITIVE ; 
 int /*<<< orphan*/  XKB_KEYSYM_NO_FLAGS ; 
 scalar_t__ xkb_keysym_from_name (char const*,int /*<<< orphan*/ ) ; 

int
glfw_xkb_keysym_from_name(const char *name, GLFWbool case_sensitive) {
    return (int)xkb_keysym_from_name(name, case_sensitive ? XKB_KEYSYM_NO_FLAGS : XKB_KEYSYM_CASE_INSENSITIVE);
}