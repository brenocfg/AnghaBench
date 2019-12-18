#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  id; int /*<<< orphan*/  surface; int /*<<< orphan*/  colormap; } ;
typedef  TYPE_1__ dialog_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  dialogs ; 
 int /*<<< orphan*/  draw_util_surface_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  xcb_destroy_window (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_free_colormap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sighandler_destroy_dialogs(void) {
    while (!TAILQ_EMPTY(&dialogs)) {
        dialog_t *dialog = TAILQ_FIRST(&dialogs);

        xcb_free_colormap(conn, dialog->colormap);
        draw_util_surface_free(conn, &(dialog->surface));
        xcb_destroy_window(conn, dialog->id);

        TAILQ_REMOVE(&dialogs, dialog, dialogs);
        free(dialog);
    }

    xcb_flush(conn);
}