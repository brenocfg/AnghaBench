#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_4__ ;
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_1__ ;
typedef  struct TYPE_33__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_generic_event_t ;
struct TYPE_35__ {scalar_t__ detail; scalar_t__ response_type; int state; int /*<<< orphan*/  time; } ;
typedef  TYPE_2__ xcb_button_press_event_t ;
typedef  int /*<<< orphan*/  position_t ;
typedef  int /*<<< orphan*/  click_destination_t ;
struct TYPE_37__ {scalar_t__ border; scalar_t__ whole_window; int /*<<< orphan*/  exclude_titlebar; } ;
struct TYPE_36__ {TYPE_1__* parent; int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;
struct TYPE_34__ {scalar_t__ type; scalar_t__ layout; int /*<<< orphan*/  focus_head; } ;
struct TYPE_33__ {int /*<<< orphan*/  focus_head; } ;
typedef  TYPE_3__ Con ;
typedef  int /*<<< orphan*/  CommandResult ;
typedef  TYPE_4__ Binding ;

/* Variables and functions */
 int /*<<< orphan*/  AFTER ; 
 int /*<<< orphan*/  BEFORE ; 
 int /*<<< orphan*/  const CLICK_BORDER ; 
 int /*<<< orphan*/  const CLICK_DECORATION ; 
 int /*<<< orphan*/  const CLICK_INSIDE ; 
 scalar_t__ CT_DOCKAREA ; 
 int /*<<< orphan*/  DLOG (char*,...) ; 
 scalar_t__ L_STACKED ; 
 scalar_t__ L_TABBED ; 
 TYPE_3__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XCB_ALLOW_ASYNC_POINTER ; 
 int /*<<< orphan*/  XCB_ALLOW_REPLAY_POINTER ; 
 scalar_t__ XCB_BUTTON_CLICK_LEFT ; 
 scalar_t__ XCB_BUTTON_CLICK_RIGHT ; 
 scalar_t__ XCB_BUTTON_RELEASE ; 
 scalar_t__ XCB_BUTTON_SCROLL_DOWN ; 
 scalar_t__ XCB_BUTTON_SCROLL_LEFT ; 
 scalar_t__ XCB_BUTTON_SCROLL_RIGHT ; 
 scalar_t__ XCB_BUTTON_SCROLL_UP ; 
 int XCB_KEY_BUT_MASK_SHIFT ; 
 int /*<<< orphan*/  command_result_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  con_activate (TYPE_3__*) ; 
 TYPE_3__* con_descend_focused (TYPE_3__*) ; 
 int /*<<< orphan*/  con_get_fullscreen_covering_ws (TYPE_3__*) ; 
 int /*<<< orphan*/  con_get_output (TYPE_3__*) ; 
 TYPE_3__* con_get_workspace (TYPE_3__*) ; 
 TYPE_3__* con_inside_floating (TYPE_3__*) ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  floating_drag_window (TYPE_3__*,TYPE_2__*,int) ; 
 scalar_t__ floating_mod_on_tiled_client (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  floating_resize_window (TYPE_3__*,int const,TYPE_2__*) ; 
 TYPE_3__* focused ; 
 TYPE_4__* get_binding_from_xcb_event (int /*<<< orphan*/ *) ; 
 TYPE_3__* get_tree_next_sibling (TYPE_3__*,int /*<<< orphan*/  const) ; 
 TYPE_12__* output_get_content (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * run_binding (TYPE_4__*,TYPE_3__*) ; 
 scalar_t__ tiling_resize (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  tree_render () ; 
 int /*<<< orphan*/  workspace_show (TYPE_3__*) ; 
 int /*<<< orphan*/  xcb_allow_events (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int route_click(Con *con, xcb_button_press_event_t *event, const bool mod_pressed, const click_destination_t dest) {
    DLOG("--> click properties: mod = %d, destination = %d\n", mod_pressed, dest);
    DLOG("--> OUTCOME = %p\n", con);
    DLOG("type = %d, name = %s\n", con->type, con->name);

    /* don’t handle dockarea cons, they must not be focused */
    if (con->parent->type == CT_DOCKAREA)
        goto done;

    const bool is_left_or_right_click = (event->detail == XCB_BUTTON_CLICK_LEFT ||
                                         event->detail == XCB_BUTTON_CLICK_RIGHT);

    /* if the user has bound an action to this click, it should override the
     * default behavior. */
    if (dest == CLICK_DECORATION || dest == CLICK_INSIDE || dest == CLICK_BORDER) {
        Binding *bind = get_binding_from_xcb_event((xcb_generic_event_t *)event);

        if (bind != NULL && ((dest == CLICK_DECORATION && !bind->exclude_titlebar) ||
                             (dest == CLICK_INSIDE && bind->whole_window) ||
                             (dest == CLICK_BORDER && bind->border))) {
            CommandResult *result = run_binding(bind, con);

            /* ASYNC_POINTER eats the event */
            xcb_allow_events(conn, XCB_ALLOW_ASYNC_POINTER, event->time);
            xcb_flush(conn);

            command_result_free(result);
            return 0;
        }
    }

    /* There is no default behavior for button release events so we are done. */
    if (event->response_type == XCB_BUTTON_RELEASE) {
        goto done;
    }

    /* Any click in a workspace should focus that workspace. If the
     * workspace is on another output we need to do a workspace_show in
     * order for i3bar (and others) to notice the change in workspace. */
    Con *ws = con_get_workspace(con);
    Con *focused_workspace = con_get_workspace(focused);

    if (!ws) {
        ws = TAILQ_FIRST(&(output_get_content(con_get_output(con))->focus_head));
        if (!ws)
            goto done;
    }

    if (ws != focused_workspace)
        workspace_show(ws);

    /* get the floating con */
    Con *floatingcon = con_inside_floating(con);
    const bool proportional = (event->state & XCB_KEY_BUT_MASK_SHIFT) == XCB_KEY_BUT_MASK_SHIFT;
    const bool in_stacked = (con->parent->layout == L_STACKED || con->parent->layout == L_TABBED);
    const bool was_focused = focused == con;

    /* 1: see if the user scrolled on the decoration of a stacked/tabbed con */
    if (in_stacked &&
        dest == CLICK_DECORATION &&
        (event->detail == XCB_BUTTON_SCROLL_UP ||
         event->detail == XCB_BUTTON_SCROLL_DOWN ||
         event->detail == XCB_BUTTON_SCROLL_LEFT ||
         event->detail == XCB_BUTTON_SCROLL_RIGHT)) {
        DLOG("Scrolling on a window decoration\n");
        /* Use the focused child of the tabbed / stacked container, not the
         * container the user scrolled on. */
        Con *current = TAILQ_FIRST(&(con->parent->focus_head));
        const position_t direction =
            (event->detail == XCB_BUTTON_SCROLL_UP || event->detail == XCB_BUTTON_SCROLL_LEFT) ? BEFORE : AFTER;
        Con *next = get_tree_next_sibling(current, direction);
        con_activate(con_descend_focused(next ? next : current));

        goto done;
    }

    /* 2: focus this con. */
    con_activate(con);

    /* 3: For floating containers, we also want to raise them on click.
     * We will skip handling events on floating cons in fullscreen mode */
    Con *fs = con_get_fullscreen_covering_ws(ws);
    if (floatingcon != NULL && fs != con) {
        /* 4: floating_modifier plus left mouse button drags */
        if (mod_pressed && event->detail == XCB_BUTTON_CLICK_LEFT) {
            floating_drag_window(floatingcon, event, false);
            return 1;
        }

        /*  5: resize (floating) if this was a (left or right) click on the
         * left/right/bottom border, or a right click on the decoration.
         * also try resizing (tiling) if it was a click on the top */
        if (mod_pressed && event->detail == XCB_BUTTON_CLICK_RIGHT) {
            DLOG("floating resize due to floatingmodifier\n");
            floating_resize_window(floatingcon, proportional, event);
            return 1;
        }

        if (!in_stacked && dest == CLICK_DECORATION &&
            is_left_or_right_click) {
            /* try tiling resize, but continue if it doesn’t work */
            DLOG("tiling resize with fallback\n");
            if (tiling_resize(con, event, dest, !was_focused))
                goto done;
        }

        if (dest == CLICK_DECORATION && event->detail == XCB_BUTTON_CLICK_RIGHT) {
            DLOG("floating resize due to decoration right click\n");
            floating_resize_window(floatingcon, proportional, event);
            return 1;
        }

        if (dest == CLICK_BORDER && is_left_or_right_click) {
            DLOG("floating resize due to border click\n");
            floating_resize_window(floatingcon, proportional, event);
            return 1;
        }

        /* 6: dragging, if this was a click on a decoration (which did not lead
         * to a resize) */
        if (dest == CLICK_DECORATION && event->detail == XCB_BUTTON_CLICK_LEFT) {
            floating_drag_window(floatingcon, event, !was_focused);
            return 1;
        }

        goto done;
    }

    /* 7: floating modifier pressed, initiate a resize */
    if (dest == CLICK_INSIDE && mod_pressed && event->detail == XCB_BUTTON_CLICK_RIGHT) {
        if (floating_mod_on_tiled_client(con, event))
            return 1;
    }
    /* 8: otherwise, check for border/decoration clicks and resize */
    else if ((dest == CLICK_BORDER || dest == CLICK_DECORATION) &&
             is_left_or_right_click) {
        DLOG("Trying to resize (tiling)\n");
        /* Since we updated the tree (con_activate() above), we need to
         * re-render the tree before returning to the event loop (drag_pointer()
         * inside tiling_resize() runs its own event-loop). */
        tree_render();
        tiling_resize(con, event, dest, dest == CLICK_DECORATION && !was_focused);
    }

done:
    xcb_allow_events(conn, XCB_ALLOW_REPLAY_POINTER, event->time);
    xcb_flush(conn);
    tree_render();

    return 0;
}