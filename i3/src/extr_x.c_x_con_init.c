#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_window_t ;
typedef  int /*<<< orphan*/  xcb_visualid_t ;
typedef  void* xcb_colormap_t ;
typedef  int uint32_t ;
struct con_state {int mapped; int initial; int /*<<< orphan*/  id; } ;
struct TYPE_10__ {int /*<<< orphan*/  id; } ;
struct TYPE_9__ {int black_pixel; } ;
struct TYPE_8__ {TYPE_5__ frame; int /*<<< orphan*/  depth; void* colormap; } ;
struct TYPE_7__ {int member_0; int member_1; int member_2; int member_3; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_1__ Rect ;
typedef  TYPE_2__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  CIRCLEQ_INSERT_HEAD (int /*<<< orphan*/ *,struct con_state*,struct con_state*) ; 
 int /*<<< orphan*/  DLOG (char*,int /*<<< orphan*/ ) ; 
 int FRAME_EVENT_MASK ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct con_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XCB_ATOM_STRING ; 
 int /*<<< orphan*/  XCB_ATOM_WM_CLASS ; 
 int /*<<< orphan*/  XCB_COLORMAP_ALLOC_NONE ; 
 int XCB_CW_BACK_PIXEL ; 
 int XCB_CW_BORDER_PIXEL ; 
 int XCB_CW_COLORMAP ; 
 int XCB_CW_EVENT_MASK ; 
 int XCB_CW_OVERRIDE_REDIRECT ; 
 int XCB_EVENT_MASK_ENTER_WINDOW ; 
 void* XCB_NONE ; 
 int /*<<< orphan*/  XCB_PROP_MODE_REPLACE ; 
 int /*<<< orphan*/  XCB_WINDOW_CLASS_INPUT_OUTPUT ; 
 int /*<<< orphan*/  XCURSOR_CURSOR_POINTER ; 
 void* colormap ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  create_window (int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  draw_util_surface_init (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_visualid_by_depth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_visualtype_by_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initial_mapping_head ; 
 int /*<<< orphan*/  initial_mapping_order ; 
 struct con_state* old_state ; 
 int /*<<< orphan*/  old_state_head ; 
 int /*<<< orphan*/  root ; 
 int /*<<< orphan*/  root_depth ; 
 TYPE_4__* root_screen ; 
 struct con_state* scalloc (int,int) ; 
 int /*<<< orphan*/  state_head ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  xcb_change_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  xcb_create_colormap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* xcb_generate_id (int /*<<< orphan*/ ) ; 

void x_con_init(Con *con) {
    /* TODO: maybe create the window when rendering first? we could then even
     * get the initial geometry right */

    uint32_t mask = 0;
    uint32_t values[5];

    xcb_visualid_t visual = get_visualid_by_depth(con->depth);
    xcb_colormap_t win_colormap;
    if (con->depth != root_depth) {
        /* We need to create a custom colormap. */
        win_colormap = xcb_generate_id(conn);
        xcb_create_colormap(conn, XCB_COLORMAP_ALLOC_NONE, win_colormap, root, visual);
        con->colormap = win_colormap;
    } else {
        /* Use the default colormap. */
        win_colormap = colormap;
        con->colormap = XCB_NONE;
    }

    /* We explicitly set a background color and border color (even though we
     * don’t even have a border) because the X11 server requires us to when
     * using 32 bit color depths, see
     * https://stackoverflow.com/questions/3645632 */
    mask |= XCB_CW_BACK_PIXEL;
    values[0] = root_screen->black_pixel;

    mask |= XCB_CW_BORDER_PIXEL;
    values[1] = root_screen->black_pixel;

    /* our own frames should not be managed */
    mask |= XCB_CW_OVERRIDE_REDIRECT;
    values[2] = 1;

    /* see include/xcb.h for the FRAME_EVENT_MASK */
    mask |= XCB_CW_EVENT_MASK;
    values[3] = FRAME_EVENT_MASK & ~XCB_EVENT_MASK_ENTER_WINDOW;

    mask |= XCB_CW_COLORMAP;
    values[4] = win_colormap;

    Rect dims = {-15, -15, 10, 10};
    xcb_window_t frame_id = create_window(conn, dims, con->depth, visual, XCB_WINDOW_CLASS_INPUT_OUTPUT, XCURSOR_CURSOR_POINTER, false, mask, values);
    draw_util_surface_init(conn, &(con->frame), frame_id, get_visualtype_by_id(visual), dims.width, dims.height);
    xcb_change_property(conn,
                        XCB_PROP_MODE_REPLACE,
                        con->frame.id,
                        XCB_ATOM_WM_CLASS,
                        XCB_ATOM_STRING,
                        8,
                        (strlen("i3-frame") + 1) * 2,
                        "i3-frame\0i3-frame\0");

    struct con_state *state = scalloc(1, sizeof(struct con_state));
    state->id = con->frame.id;
    state->mapped = false;
    state->initial = true;
    DLOG("Adding window 0x%08x to lists\n", state->id);
    CIRCLEQ_INSERT_HEAD(&state_head, state, state);
    CIRCLEQ_INSERT_HEAD(&old_state_head, state, old_state);
    TAILQ_INSERT_TAIL(&initial_mapping_head, state, initial_mapping_order);
    DLOG("adding new state for window id 0x%08x\n", state->id);
}