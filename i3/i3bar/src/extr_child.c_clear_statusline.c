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
struct statusline_head {int dummy; } ;
struct status_block {int /*<<< orphan*/  border; int /*<<< orphan*/  background; int /*<<< orphan*/  min_width_str; int /*<<< orphan*/  instance; int /*<<< orphan*/  name; int /*<<< orphan*/  color; int /*<<< orphan*/  short_text; int /*<<< orphan*/  full_text; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I3STRING_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_EMPTY (struct statusline_head*) ; 
 struct status_block* TAILQ_FIRST (struct statusline_head*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct statusline_head*,struct status_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blocks ; 
 int /*<<< orphan*/  free (struct status_block*) ; 

__attribute__((used)) static void clear_statusline(struct statusline_head *head, bool free_resources) {
    struct status_block *first;
    while (!TAILQ_EMPTY(head)) {
        first = TAILQ_FIRST(head);
        if (free_resources) {
            I3STRING_FREE(first->full_text);
            I3STRING_FREE(first->short_text);
            FREE(first->color);
            FREE(first->name);
            FREE(first->instance);
            FREE(first->min_width_str);
            FREE(first->background);
            FREE(first->border);
        }

        TAILQ_REMOVE(head, first, blocks);
        free(first);
    }
}