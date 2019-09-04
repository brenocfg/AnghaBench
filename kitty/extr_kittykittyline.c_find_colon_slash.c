#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t index_type ;
typedef  enum URL_PARSER_STATES { ____Placeholder_URL_PARSER_STATES } URL_PARSER_STATES ;
typedef  char char_type ;
struct TYPE_5__ {size_t xnum; TYPE_1__* cpu_cells; } ;
struct TYPE_4__ {char ch; } ;
typedef  TYPE_2__ Line ;

/* Variables and functions */
 size_t MAX (int,size_t) ; 
 int /*<<< orphan*/  is_url_char (char) ; 

__attribute__((used)) static inline index_type
find_colon_slash(Line *self, index_type x, index_type limit) {
    // Find :// at or before x
    index_type pos = x;
    enum URL_PARSER_STATES {ANY, FIRST_SLASH, SECOND_SLASH};
    enum URL_PARSER_STATES state = ANY;
    limit = MAX(2, limit);
    if (pos < limit) return 0;
    do {
        char_type ch = self->cpu_cells[pos].ch;
        if (!is_url_char(ch)) return false;
        if (pos == x) {
            if (ch == ':') {
                if (pos + 2 < self->xnum && self->cpu_cells[pos+1].ch == '/' && self->cpu_cells[pos + 2].ch == '/') state = SECOND_SLASH;
            } else if (ch == '/') {
                if (pos + 1 < self->xnum && self->cpu_cells[pos+1].ch == '/') state = FIRST_SLASH;
            }
        }
        switch(state) {
            case ANY:
                if (ch == '/') state = FIRST_SLASH;
                break;
            case FIRST_SLASH:
                state = ch == '/' ? SECOND_SLASH : ANY;
                break;
            case SECOND_SLASH:
                if (ch == ':') return pos;
                state = ANY;
                break;
        }
        pos--;
    } while(pos >= limit);
    return 0;
}