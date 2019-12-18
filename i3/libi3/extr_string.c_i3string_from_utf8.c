#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  i3String ;

/* Variables and functions */
 int /*<<< orphan*/ * i3string_from_utf8_with_length (char const*,int) ; 

i3String *i3string_from_utf8(const char *from_utf8) {
    return i3string_from_utf8_with_length(from_utf8, -1);
}