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
typedef  scalar_t__ index_type ;
struct TYPE_5__ {scalar_t__ xnum; TYPE_1__* cpu_cells; } ;
struct TYPE_4__ {int /*<<< orphan*/  ch; } ;
typedef  TYPE_2__ Line ;

/* Variables and functions */
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 scalar_t__ MIN_URL_LEN ; 
 int /*<<< orphan*/  is_url_char (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
has_url_beyond(Line *self, index_type x) {
    if (self->xnum <= x + MIN_URL_LEN + 3) return false;
    for (index_type i = x; i < MIN(x + MIN_URL_LEN + 3, self->xnum); i++) {
        if (!is_url_char(self->cpu_cells[i].ch)) return false;
    }
    return true;
}