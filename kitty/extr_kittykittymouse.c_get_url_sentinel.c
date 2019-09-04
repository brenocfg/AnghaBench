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
typedef  int index_type ;
typedef  int char_type ;
struct TYPE_5__ {int xnum; TYPE_1__* cpu_cells; } ;
struct TYPE_4__ {int ch; } ;
typedef  TYPE_2__ Line ;

/* Variables and functions */

__attribute__((used)) static inline char_type
get_url_sentinel(Line *line, index_type url_start) {
    char_type before = 0, sentinel;
    if (url_start > 0 && url_start < line->xnum) before = line->cpu_cells[url_start - 1].ch;
    switch(before) {
        case '"':
        case '\'':
        case '*':
            sentinel = before; break;
        case '(':
            sentinel = ')'; break;
        case '[':
            sentinel = ']'; break;
        case '{':
            sentinel = '}'; break;
        case '<':
            sentinel = '>'; break;
        default:
            sentinel = 0; break;
    }
    return sentinel;
}