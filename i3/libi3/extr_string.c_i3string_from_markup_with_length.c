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
struct TYPE_4__ {int pango_markup; } ;
typedef  TYPE_1__ i3String ;

/* Variables and functions */
 TYPE_1__* i3string_from_utf8_with_length (char const*,size_t) ; 

i3String *i3string_from_markup_with_length(const char *from_markup, size_t num_bytes) {
    i3String *str = i3string_from_utf8_with_length(from_markup, num_bytes);

    /* set the markup flag */
    str->pango_markup = true;

    return str;
}