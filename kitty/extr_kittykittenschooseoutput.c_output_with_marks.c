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
typedef  int /*<<< orphan*/  text_t ;
typedef  size_t len_t ;
struct TYPE_3__ {scalar_t__ mark_before_sz; size_t mark_after_sz; int /*<<< orphan*/ * mark_after; int /*<<< orphan*/ * mark_before; } ;
typedef  TYPE_1__ Options ;
typedef  int /*<<< orphan*/  GlobalData ;

/* Variables and functions */
 size_t MIN (size_t,size_t) ; 
 int /*<<< orphan*/  output_text (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void
output_with_marks(GlobalData *global, Options *opts, text_t *src, size_t src_sz, len_t *positions, len_t poslen) {
    size_t pos, i = 0;
    for (pos = 0; pos < poslen; pos++, i++) {
        output_text(global, src + i, MIN(src_sz, positions[pos]) - i);
        i = positions[pos];
        if (i < src_sz) {
            if (opts->mark_before_sz > 0) output_text(global, opts->mark_before, opts->mark_before_sz);
            output_text(global, src + i, 1);
            if (opts->mark_after_sz > 0) output_text(global, opts->mark_after, opts->mark_after_sz);
        }
    }
    i = positions[poslen - 1];
    if (i + 1 < src_sz) output_text(global, src + i + 1, src_sz - i - 1);
}