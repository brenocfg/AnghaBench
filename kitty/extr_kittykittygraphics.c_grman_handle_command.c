#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_20__ {int action; int /*<<< orphan*/  id; } ;
struct TYPE_19__ {int /*<<< orphan*/  used_storage; TYPE_3__ const last_init_graphics_command; } ;
struct TYPE_18__ {int /*<<< orphan*/  data_loaded; } ;
typedef  TYPE_1__ Image ;
typedef  TYPE_2__ GraphicsManager ;
typedef  TYPE_3__ GraphicsCommand ;
typedef  int /*<<< orphan*/  Cursor ;
typedef  int /*<<< orphan*/  CellPixelSize ;

/* Variables and functions */
 int /*<<< orphan*/  REPORT_ERROR (char*,...) ; 
 int /*<<< orphan*/  STORAGE_LIMIT ; 
 int /*<<< orphan*/  add_trim_predicate ; 
 int /*<<< orphan*/  apply_storage_quota (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 char* create_add_response (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* handle_add_command (TYPE_2__*,TYPE_3__ const*,int /*<<< orphan*/  const*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_delete_command (TYPE_2__*,TYPE_3__ const*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_put_command (TYPE_2__*,TYPE_3__ const*,int /*<<< orphan*/ *,int*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_images (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

const char*
grman_handle_command(GraphicsManager *self, const GraphicsCommand *g, const uint8_t *payload, Cursor *c, bool *is_dirty, CellPixelSize cell) {
    Image *image;
    const char *ret = NULL;
    uint32_t iid, q_iid;

    switch(g->action) {
        case 0:
        case 't':
        case 'T':
        case 'q':
            iid = g->id; q_iid = iid;
            if (g->action == 'q') { iid = 0; if (!q_iid) { REPORT_ERROR("Query graphics command without image id"); break; } }
            image = handle_add_command(self, g, payload, is_dirty, iid);
            ret = create_add_response(self, image != NULL, g->action == 'q' ? q_iid: self->last_init_graphics_command.id);
            if (self->last_init_graphics_command.action == 'T' && image && image->data_loaded) handle_put_command(self, &self->last_init_graphics_command, c, is_dirty, image, cell);
            if (g->action == 'q') remove_images(self, add_trim_predicate, NULL);
            if (self->used_storage > STORAGE_LIMIT) apply_storage_quota(self, STORAGE_LIMIT, image);
            break;
        case 'p':
            if (!g->id) {
                REPORT_ERROR("Put graphics command without image id");
                break;
            }
            handle_put_command(self, g, c, is_dirty, NULL, cell);
            ret = create_add_response(self, true, g->id);
            break;
        case 'd':
            handle_delete_command(self, g, c, is_dirty, cell);
            break;
        default:
            REPORT_ERROR("Unknown graphics command action: %c", g->action);
            break;
    }
    return ret;
}