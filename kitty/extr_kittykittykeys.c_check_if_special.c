#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
typedef  int ssize_t ;
struct TYPE_2__ {int scancode; int mods; } ;

/* Variables and functions */
 size_t SPECIAL_INDEX (size_t) ; 
 size_t UINT8_MAX ; 
 scalar_t__ arraysz (size_t*) ; 
 size_t* key_map ; 
 TYPE_1__* native_special_keys ; 
 size_t native_special_keys_count ; 
 int* needs_special_handling ; 

__attribute__((used)) static inline bool
check_if_special(int key, int mods, int scancode) {
    uint16_t qkey = (0 <= key && key < (ssize_t)arraysz(key_map)) ? key_map[key] : UINT8_MAX;
    bool special = false;
    if (qkey != UINT8_MAX) {
        qkey = SPECIAL_INDEX(qkey);
        special = needs_special_handling[qkey];
    }
    for (size_t i = 0; !special && i < native_special_keys_count; i++) {
        if (scancode == native_special_keys[i].scancode && mods == native_special_keys[i].mods) special = true;
    }
    return special;
}