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

__attribute__((used)) static size_t handle_special_paths(const char *path, size_t off, size_t last_slash)
{
    size_t orig_off = off, part_size = off - last_slash;

    if (part_size == 2 && path[off - 1] == '.') {
        --off;
    } else if (part_size == 3 && path[off - 2] == '.' && path[off - 1] == '.') {
        off -= 2;
        if (off > 1) {
            for (--off; path[off - 1] != '/'; --off)
                ;
        }
    }
    return orig_off - off;
}