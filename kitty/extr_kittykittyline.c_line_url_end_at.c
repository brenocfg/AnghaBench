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
typedef  scalar_t__ char_type ;
struct TYPE_5__ {size_t xnum; TYPE_1__* cpu_cells; } ;
struct TYPE_4__ {scalar_t__ ch; } ;
typedef  TYPE_2__ Line ;

/* Variables and functions */
 size_t MIN_URL_LEN ; 
 scalar_t__ can_strip_from_end_of_url (scalar_t__) ; 
 scalar_t__ is_url_char (scalar_t__) ; 

index_type
line_url_end_at(Line *self, index_type x, bool check_short, char_type sentinel) {
    index_type ans = x;
    if (x >= self->xnum || (check_short && self->xnum <= MIN_URL_LEN + 3)) return 0;
    if (sentinel) { while (ans < self->xnum && self->cpu_cells[ans].ch != sentinel && is_url_char(self->cpu_cells[ans].ch)) ans++; }
    else { while (ans < self->xnum && is_url_char(self->cpu_cells[ans].ch)) ans++; }
    if (ans) ans--;
    while (ans > x && can_strip_from_end_of_url(self->cpu_cells[ans].ch)) ans--;
    return ans;
}