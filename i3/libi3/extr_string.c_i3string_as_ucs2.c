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
typedef  int /*<<< orphan*/  xcb_char2b_t ;
struct TYPE_4__ {int /*<<< orphan*/  const* ucs2; } ;
typedef  TYPE_1__ i3String ;

/* Variables and functions */
 int /*<<< orphan*/  i3string_ensure_ucs2 (TYPE_1__*) ; 

const xcb_char2b_t *i3string_as_ucs2(i3String *str) {
    i3string_ensure_ucs2(str);
    return str->ucs2;
}