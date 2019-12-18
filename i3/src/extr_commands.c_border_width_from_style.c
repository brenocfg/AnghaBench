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
typedef  scalar_t__ border_style_t ;
struct TYPE_2__ {scalar_t__ default_floating_border; int default_floating_border_width; scalar_t__ default_border; int default_border_width; } ;
typedef  int /*<<< orphan*/  Con ;

/* Variables and functions */
 scalar_t__ BS_NONE ; 
 scalar_t__ BS_NORMAL ; 
 int /*<<< orphan*/ * con_inside_floating (int /*<<< orphan*/ *) ; 
 TYPE_1__ config ; 
 int logical_px (int) ; 

__attribute__((used)) static int border_width_from_style(border_style_t border_style, long border_width, Con *con) {
    if (border_style == BS_NONE) {
        return 0;
    }
    if (border_width >= 0) {
        return logical_px(border_width);
    }

    const bool is_floating = con_inside_floating(con) != NULL;
    /* Load the configured defaults. */
    if (is_floating && border_style == config.default_floating_border) {
        return config.default_floating_border_width;
    } else if (!is_floating && border_style == config.default_border) {
        return config.default_border_width;
    } else {
        /* Use some hardcoded values. */
        return logical_px(border_style == BS_NORMAL ? 2 : 1);
    }
}