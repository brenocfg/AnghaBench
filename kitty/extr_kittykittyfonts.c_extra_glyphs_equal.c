#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__* data; } ;
typedef  TYPE_1__ ExtraGlyphs ;

/* Variables and functions */
 size_t MAX_NUM_EXTRA_GLYPHS ; 

__attribute__((used)) static inline bool
extra_glyphs_equal(ExtraGlyphs *a, ExtraGlyphs *b) {
    for (size_t i = 0; i < MAX_NUM_EXTRA_GLYPHS; i++) {
        if (a->data[i] != b->data[i]) return false;
        if (a->data[i] == 0) return true;
    }
    return true;
}