#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  index_type ;
struct TYPE_4__ {int /*<<< orphan*/ * line; } ;
typedef  TYPE_1__ LineBuf ;
typedef  int /*<<< orphan*/  Line ;

/* Variables and functions */
 int /*<<< orphan*/  linebuf_init_line (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline Line*
get_line(LineBuf *self, index_type y) {
    linebuf_init_line(self, y);
    return self->line;
}