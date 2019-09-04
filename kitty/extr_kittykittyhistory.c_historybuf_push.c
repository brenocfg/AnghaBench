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
struct TYPE_5__ {int start_of_data; int count; int ynum; int /*<<< orphan*/  line; } ;
typedef  TYPE_1__ HistoryBuf ;

/* Variables and functions */
 int /*<<< orphan*/  init_line (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pagerhist_push (TYPE_1__*) ; 

__attribute__((used)) static inline index_type
historybuf_push(HistoryBuf *self) {
    index_type idx = (self->start_of_data + self->count) % self->ynum;
    init_line(self, idx, self->line);
    if (self->count == self->ynum) {
        pagerhist_push(self);
        self->start_of_data = (self->start_of_data + 1) % self->ynum;
    } else self->count++;
    return idx;
}