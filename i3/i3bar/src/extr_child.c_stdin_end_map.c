#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct status_block {char* min_width_str; int /*<<< orphan*/  pango_markup; int /*<<< orphan*/ * short_text; int /*<<< orphan*/ * full_text; scalar_t__ min_width; scalar_t__ urgent; } ;
struct TYPE_2__ {int has_urgent; int /*<<< orphan*/  block; } ;
typedef  TYPE_1__ parser_ctx ;
typedef  int /*<<< orphan*/  i3String ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct status_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blocks ; 
 int /*<<< orphan*/  i3string_free (int /*<<< orphan*/ *) ; 
 void* i3string_from_utf8 (char*) ; 
 int /*<<< orphan*/  i3string_set_markup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct status_block*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ predict_text_width (int /*<<< orphan*/ *) ; 
 struct status_block* smalloc (int) ; 
 int /*<<< orphan*/  statusline_buffer ; 

__attribute__((used)) static int stdin_end_map(void *context) {
    parser_ctx *ctx = context;
    struct status_block *new_block = smalloc(sizeof(struct status_block));
    memcpy(new_block, &(ctx->block), sizeof(struct status_block));
    /* Ensure we have a full_text set, so that when it is missing (or null),
     * i3bar doesn’t crash and the user gets an annoying message. */
    if (!new_block->full_text)
        new_block->full_text = i3string_from_utf8("SPEC VIOLATION: full_text is NULL!");
    if (new_block->urgent)
        ctx->has_urgent = true;

    if (new_block->min_width_str) {
        i3String *text = i3string_from_utf8(new_block->min_width_str);
        i3string_set_markup(text, new_block->pango_markup);
        new_block->min_width = (uint32_t)predict_text_width(text);
        i3string_free(text);
    }

    i3string_set_markup(new_block->full_text, new_block->pango_markup);

    if (new_block->short_text != NULL)
        i3string_set_markup(new_block->short_text, new_block->pango_markup);

    TAILQ_INSERT_TAIL(&statusline_buffer, new_block, blocks);
    return 1;
}