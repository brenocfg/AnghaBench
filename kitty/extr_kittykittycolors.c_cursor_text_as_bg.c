#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int cursor_text_uses_bg; } ;
struct TYPE_5__ {int cursor_text_uses_bg; } ;
struct TYPE_7__ {TYPE_2__ configured; TYPE_1__ overridden; } ;
typedef  TYPE_3__ ColorProfile ;

/* Variables and functions */

float
cursor_text_as_bg(ColorProfile *self) {
    if (self->overridden.cursor_text_uses_bg & 1) {
        return self->overridden.cursor_text_uses_bg & 2 ? 1.f : 0.f;
    }
    return self->configured.cursor_text_uses_bg & 2 ? 1.f : 0.f;
}