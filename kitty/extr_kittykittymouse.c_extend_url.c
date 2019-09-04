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
typedef  int index_type ;
typedef  int /*<<< orphan*/  char_type ;
struct TYPE_5__ {int xnum; } ;
typedef  int /*<<< orphan*/  Screen ;
typedef  TYPE_1__ Line ;

/* Variables and functions */
 int line_url_end_at (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* screen_visual_line (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void
extend_url(Screen *screen, Line *line, index_type *x, index_type *y, char_type sentinel) {
    unsigned int count = 0;
    while(count++ < 10) {
        if (*x != line->xnum - 1) break;
        line = screen_visual_line(screen, *y + 1);
        if (!line) break; // we deliberately allow non-continued lines as some programs, like mutt split URLs with newlines at line boundaries
        index_type new_x = line_url_end_at(line, 0, false, sentinel);
        if (!new_x) break;
        *y += 1; *x = new_x;
    }
}