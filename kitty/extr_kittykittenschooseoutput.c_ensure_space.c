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
struct TYPE_3__ {size_t output_sz; size_t output_pos; int /*<<< orphan*/  output; } ;
typedef  TYPE_1__ GlobalData ;

/* Variables and functions */
 scalar_t__ MAX (size_t,int) ; 
 int /*<<< orphan*/  realloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline bool
ensure_space(GlobalData *global, size_t sz) {
    if (global->output_sz < sz + global->output_pos) {
        size_t before = global->output_sz;
        global->output_sz += MAX(sz, (64 * 1024));
        global->output = realloc(global->output, sizeof(text_t) * global->output_sz);
        if (!global->output) {
            global->output_sz = before;
            return false;
        }
    }
    return true;
}