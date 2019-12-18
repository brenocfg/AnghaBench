#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_timestamp_t ;
typedef  scalar_t__ xcb_randr_output_t ;
typedef  int /*<<< orphan*/  xcb_randr_get_screen_resources_current_reply_t ;
struct TYPE_16__ {scalar_t__ crtc; } ;
typedef  TYPE_2__ xcb_randr_get_output_info_reply_t ;
struct TYPE_15__ {scalar_t__ x; scalar_t__ y; scalar_t__ width; scalar_t__ height; } ;
struct TYPE_17__ {int primary; int active; int to_be_disabled; int changed; TYPE_1__ rect; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  names_head; scalar_t__ id; } ;
typedef  TYPE_3__ xcb_randr_get_crtc_info_reply_t ;
typedef  int /*<<< orphan*/  xcb_randr_get_crtc_info_cookie_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
struct output_name {struct output_name* name; } ;
struct TYPE_18__ {scalar_t__ output; } ;
typedef  TYPE_3__ Output ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,...) ; 
 int /*<<< orphan*/  FREE (struct output_name*) ; 
 int /*<<< orphan*/  SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct output_name* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct output_name*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ XCB_NONE ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 TYPE_3__* get_output_by_id (scalar_t__) ; 
 int /*<<< orphan*/  names ; 
 int /*<<< orphan*/  output_primary_name (TYPE_3__*) ; 
 int /*<<< orphan*/  outputs ; 
 TYPE_8__* primary ; 
 int /*<<< orphan*/  sasprintf (struct output_name**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* scalloc (int,int) ; 
 int update_if_necessary (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_randr_get_crtc_info (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_3__* xcb_randr_get_crtc_info_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_randr_get_output_info_name (TYPE_2__*) ; 
 int /*<<< orphan*/  xcb_randr_get_output_info_name_length (TYPE_2__*) ; 

__attribute__((used)) static void handle_output(xcb_connection_t *conn, xcb_randr_output_t id,
                          xcb_randr_get_output_info_reply_t *output,
                          xcb_timestamp_t cts,
                          xcb_randr_get_screen_resources_current_reply_t *res) {
    /* each CRT controller has a position in which we are interested in */
    xcb_randr_get_crtc_info_reply_t *crtc;

    Output *new = get_output_by_id(id);
    bool existing = (new != NULL);
    if (!existing) {
        new = scalloc(1, sizeof(Output));
        SLIST_INIT(&new->names_head);
    }
    new->id = id;
    new->primary = (primary && primary->output == id);
    while (!SLIST_EMPTY(&new->names_head)) {
        FREE(SLIST_FIRST(&new->names_head)->name);
        struct output_name *old_head = SLIST_FIRST(&new->names_head);
        SLIST_REMOVE_HEAD(&new->names_head, names);
        FREE(old_head);
    }
    struct output_name *output_name = scalloc(1, sizeof(struct output_name));
    sasprintf(&output_name->name, "%.*s",
              xcb_randr_get_output_info_name_length(output),
              xcb_randr_get_output_info_name(output));
    SLIST_INSERT_HEAD(&new->names_head, output_name, names);

    DLOG("found output with name %s\n", output_primary_name(new));

    /* Even if no CRTC is used at the moment, we store the output so that
     * we do not need to change the list ever again (we only update the
     * position/size) */
    if (output->crtc == XCB_NONE) {
        if (!existing) {
            if (new->primary)
                TAILQ_INSERT_HEAD(&outputs, new, outputs);
            else
                TAILQ_INSERT_TAIL(&outputs, new, outputs);
        } else if (new->active)
            new->to_be_disabled = true;
        return;
    }

    xcb_randr_get_crtc_info_cookie_t icookie;
    icookie = xcb_randr_get_crtc_info(conn, output->crtc, cts);
    if ((crtc = xcb_randr_get_crtc_info_reply(conn, icookie, NULL)) == NULL) {
        DLOG("Skipping output %s: could not get CRTC (%p)\n",
             output_primary_name(new), crtc);
        free(new);
        return;
    }

    bool updated = update_if_necessary(&(new->rect.x), crtc->x) |
                   update_if_necessary(&(new->rect.y), crtc->y) |
                   update_if_necessary(&(new->rect.width), crtc->width) |
                   update_if_necessary(&(new->rect.height), crtc->height);
    free(crtc);
    new->active = (new->rect.width != 0 && new->rect.height != 0);
    if (!new->active) {
        DLOG("width/height 0/0, disabling output\n");
        return;
    }

    DLOG("mode: %dx%d+%d+%d\n", new->rect.width, new->rect.height,
         new->rect.x, new->rect.y);

    /* If we don’t need to change an existing output or if the output
     * does not exist in the first place, the case is simple: we either
     * need to insert the new output or we are done. */
    if (!updated || !existing) {
        if (!existing) {
            if (new->primary)
                TAILQ_INSERT_HEAD(&outputs, new, outputs);
            else
                TAILQ_INSERT_TAIL(&outputs, new, outputs);
        }
        return;
    }

    new->changed = true;
}