#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pango_markup; } ;
typedef  TYPE_1__ i3String ;

/* Variables and functions */
 int /*<<< orphan*/  i3string_as_utf8 (TYPE_1__*) ; 
 TYPE_1__* i3string_from_utf8 (int /*<<< orphan*/ ) ; 

i3String *i3string_copy(i3String *str) {
    i3String *copy = i3string_from_utf8(i3string_as_utf8(str));
    copy->pango_markup = str->pango_markup;
    return copy;
}