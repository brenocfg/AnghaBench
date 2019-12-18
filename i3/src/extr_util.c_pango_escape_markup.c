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

/* Variables and functions */
 int /*<<< orphan*/  FREE (char*) ; 
 int /*<<< orphan*/  font_is_pango () ; 
 char* g_markup_escape_text (char*,int) ; 

char *pango_escape_markup(char *input) {
    if (!font_is_pango())
        return input;

    char *escaped = g_markup_escape_text(input, -1);
    FREE(input);

    return escaped;
}