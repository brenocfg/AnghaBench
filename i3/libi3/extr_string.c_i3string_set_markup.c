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
struct TYPE_3__ {int pango_markup; } ;
typedef  TYPE_1__ i3String ;

/* Variables and functions */

void i3string_set_markup(i3String *str, bool pango_markup) {
    str->pango_markup = pango_markup;
}