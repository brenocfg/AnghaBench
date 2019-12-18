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
typedef  scalar_t__ ssize_t ;
struct TYPE_4__ {size_t num_bytes; int /*<<< orphan*/  utf8; } ;
typedef  TYPE_1__ i3String ;

/* Variables and functions */
 int /*<<< orphan*/  g_utf8_make_valid (char const*,scalar_t__) ; 
 TYPE_1__* scalloc (int,int) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

i3String *i3string_from_utf8_with_length(const char *from_utf8, ssize_t num_bytes) {
    i3String *str = scalloc(1, sizeof(i3String));

    /* g_utf8_make_valid NULL-terminates the string. */
    str->utf8 = g_utf8_make_valid(from_utf8, num_bytes);

    /* num_bytes < 0 means NULL-terminated string, need to calculate length */
    str->num_bytes = num_bytes < 0 ? strlen(str->utf8) : (size_t)num_bytes;

    return str;
}