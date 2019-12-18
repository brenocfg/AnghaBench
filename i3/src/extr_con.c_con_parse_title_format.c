#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  placeholders ;
struct TYPE_7__ {char* name; char* value; } ;
typedef  TYPE_1__ placeholder_t ;
struct TYPE_8__ {char* class_class; char* class_instance; int /*<<< orphan*/ * name; } ;
typedef  TYPE_2__ i3Window ;
typedef  int /*<<< orphan*/  i3String ;
struct TYPE_9__ {int /*<<< orphan*/ * title_format; TYPE_2__* window; } ;
typedef  TYPE_3__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char* con_get_tree_representation (TYPE_3__*) ; 
 int font_is_pango () ; 
 char* format_placeholders (int /*<<< orphan*/ *,TYPE_1__*,size_t const) ; 
 char* i3string_as_utf8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * i3string_from_utf8 (char*) ; 
 int /*<<< orphan*/  i3string_set_markup (int /*<<< orphan*/ *,int const) ; 
 char* pango_escape_markup (char*) ; 
 char* sstrdup (char*) ; 

i3String *con_parse_title_format(Con *con) {
    assert(con->title_format != NULL);

    i3Window *win = con->window;

    /* We need to ensure that we only escape the window title if pango
     * is used by the current font. */
    const bool pango_markup = font_is_pango();

    char *title;
    char *class;
    char *instance;
    if (win == NULL) {
        title = pango_escape_markup(con_get_tree_representation(con));
        class = sstrdup("i3-frame");
        instance = sstrdup("i3-frame");
    } else {
        title = pango_escape_markup(sstrdup((win->name == NULL) ? "" : i3string_as_utf8(win->name)));
        class = pango_escape_markup(sstrdup((win->class_class == NULL) ? "" : win->class_class));
        instance = pango_escape_markup(sstrdup((win->class_instance == NULL) ? "" : win->class_instance));
    }

    placeholder_t placeholders[] = {
        {.name = "%title", .value = title},
        {.name = "%class", .value = class},
        {.name = "%instance", .value = instance}};
    const size_t num = sizeof(placeholders) / sizeof(placeholder_t);

    char *formatted_str = format_placeholders(con->title_format, &placeholders[0], num);
    i3String *formatted = i3string_from_utf8(formatted_str);
    i3string_set_markup(formatted, pango_markup);
    FREE(formatted_str);

    for (size_t i = 0; i < num; i++) {
        FREE(placeholders[i].value);
    }

    return formatted;
}