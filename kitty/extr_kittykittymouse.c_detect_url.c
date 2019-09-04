#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ index_type ;
typedef  int /*<<< orphan*/  char_type ;
struct TYPE_7__ {scalar_t__ xnum; } ;
typedef  int /*<<< orphan*/  Screen ;
typedef  TYPE_1__ Line ;

/* Variables and functions */
 int /*<<< orphan*/  BEAM ; 
 int /*<<< orphan*/  HAND ; 
 int /*<<< orphan*/  extend_url (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_url_sentinel (TYPE_1__*,scalar_t__) ; 
 scalar_t__ line_url_end_at (TYPE_1__*,unsigned int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ line_url_start_at (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  mouse_cursor_shape ; 
 int /*<<< orphan*/  screen_mark_url (int /*<<< orphan*/ *,scalar_t__,unsigned int,scalar_t__,scalar_t__) ; 
 TYPE_1__* screen_visual_line (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static inline void
detect_url(Screen *screen, unsigned int x, unsigned int y) {
    bool has_url = false;
    index_type url_start, url_end = 0;
    Line *line = screen_visual_line(screen, y);
    char_type sentinel;
    if (line) {
        url_start = line_url_start_at(line, x);
        sentinel = get_url_sentinel(line, url_start);
        if (url_start < line->xnum) url_end = line_url_end_at(line, x, true, sentinel);
        has_url = url_end > url_start;
    }
    if (has_url) {
        mouse_cursor_shape = HAND;
        index_type y_extended = y;
        extend_url(screen, line, &url_end, &y_extended, sentinel);
        screen_mark_url(screen, url_start, y, url_end, y_extended);
    } else {
        mouse_cursor_shape = BEAM;
        screen_mark_url(screen, 0, 0, 0, 0);
    }
}