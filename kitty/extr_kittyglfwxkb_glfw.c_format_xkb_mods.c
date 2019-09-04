#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int xkb_mod_mask_t ;
typedef  int xkb_mod_index_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {int /*<<< orphan*/  keymap; } ;
typedef  TYPE_1__ _GLFWXKBData ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 char* xkb_keymap_mod_get_name (int /*<<< orphan*/ ,int) ; 
 int xkb_keymap_num_mods (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline const char*
format_xkb_mods(_GLFWXKBData *xkb, const char* name, xkb_mod_mask_t mods) {
    static char buf[512];
    char *p = buf, *s;
#define pr(x) p += snprintf(p, sizeof(buf) - (p - buf) - 1, "%s", x)
    pr(name); pr(": ");
    s = p;
    for (xkb_mod_index_t i = 0; i < xkb_keymap_num_mods(xkb->keymap); i++) {
        xkb_mod_mask_t m = 1 << i;
        if (m & mods) { pr(xkb_keymap_mod_get_name(xkb->keymap, i)); pr("+"); }
    }
    if (p == s) pr("none");
    else p--;
    pr(" ");
#undef pr
    return buf;
}