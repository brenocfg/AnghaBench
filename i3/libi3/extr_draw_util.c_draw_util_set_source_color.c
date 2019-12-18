#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cr; } ;
typedef  TYPE_1__ surface_t ;
struct TYPE_7__ {int /*<<< orphan*/  alpha; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
typedef  TYPE_2__ color_t ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_UNLESS_SURFACE_INITIALIZED (TYPE_1__*) ; 
 int /*<<< orphan*/  cairo_set_source_rgba (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void draw_util_set_source_color(surface_t *surface, color_t color) {
    RETURN_UNLESS_SURFACE_INITIALIZED(surface);

    cairo_set_source_rgba(surface->cr, color.red, color.green, color.blue, color.alpha);
}