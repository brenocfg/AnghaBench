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
 int /*<<< orphan*/  free (char*) ; 
 char* g_markup_escape_text (char const*,int) ; 
 char* i3string_as_utf8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * i3string_from_utf8 (char*) ; 

i3String *i3string_escape_markup(i3String *str) {
    const char *text = i3string_as_utf8(str);
    char *escaped = g_markup_escape_text(text, -1);
    i3String *result = i3string_from_utf8(escaped);
    free(escaped);
    return result;
}