#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_connection_t ;
struct output_name {char* name; } ;
struct TYPE_7__ {int /*<<< orphan*/  height_in_pixels; int /*<<< orphan*/  width_in_pixels; } ;
struct TYPE_5__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_6__ {int active; int /*<<< orphan*/  names_head; TYPE_1__ rect; } ;
typedef  TYPE_2__ Output ;

/* Variables and functions */
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct output_name*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  names ; 
 TYPE_3__* root_screen ; 
 void* scalloc (int,int) ; 

Output *create_root_output(xcb_connection_t *conn) {
    Output *s = scalloc(1, sizeof(Output));

    s->active = false;
    s->rect.x = 0;
    s->rect.y = 0;
    s->rect.width = root_screen->width_in_pixels;
    s->rect.height = root_screen->height_in_pixels;

    struct output_name *output_name = scalloc(1, sizeof(struct output_name));
    output_name->name = "xroot-0";
    SLIST_INIT(&s->names_head);
    SLIST_INSERT_HEAD(&s->names_head, output_name, names);

    return s;
}