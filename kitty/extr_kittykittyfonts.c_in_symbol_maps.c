#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ char_type ;
struct TYPE_5__ {scalar_t__ left; scalar_t__ right; scalar_t__ font_idx; } ;
struct TYPE_4__ {scalar_t__ first_symbol_font_idx; } ;
typedef  TYPE_1__ FontGroup ;

/* Variables and functions */
 scalar_t__ NO_FONT ; 
 size_t num_symbol_maps ; 
 TYPE_2__* symbol_maps ; 

__attribute__((used)) static inline ssize_t
in_symbol_maps(FontGroup *fg, char_type ch) {
    for (size_t i = 0; i < num_symbol_maps; i++) {
        if (symbol_maps[i].left <= ch && ch <= symbol_maps[i].right) return fg->first_symbol_font_idx + symbol_maps[i].font_idx;
    }
    return NO_FONT;
}