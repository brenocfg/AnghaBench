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
typedef  int /*<<< orphan*/  xkb_keysym_t ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  xkb_keysym_get_name (int /*<<< orphan*/ ,char*,int) ; 

const char*
glfw_xkb_keysym_name(xkb_keysym_t sym) {
    static char name[256];
    name[0] = 0;
    xkb_keysym_get_name(sym, name, sizeof(name));
    return name;
}