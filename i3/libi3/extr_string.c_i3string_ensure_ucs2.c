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
struct TYPE_3__ {int /*<<< orphan*/  num_glyphs; int /*<<< orphan*/  utf8; int /*<<< orphan*/ * ucs2; } ;
typedef  TYPE_1__ i3String ;

/* Variables and functions */
 int /*<<< orphan*/ * convert_utf8_to_ucs2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i3string_ensure_ucs2(i3String *str) {
    if (str->ucs2 != NULL)
        return;
    str->ucs2 = convert_utf8_to_ucs2(str->utf8, &str->num_glyphs);
}