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
typedef  int /*<<< orphan*/  text_t ;
struct TYPE_4__ {scalar_t__ output_pos; scalar_t__ output; } ;
typedef  TYPE_1__ GlobalData ;

/* Variables and functions */
 scalar_t__ ensure_space (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static inline void
output_text(GlobalData *global, const text_t *data, size_t sz) {
    if (ensure_space(global, sz)) {
        memcpy(global->output + global->output_pos, data, sizeof(text_t) * sz);
        global->output_pos += sz;
    }
}