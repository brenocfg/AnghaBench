#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {size_t xnum; int /*<<< orphan*/  start_of_data; TYPE_1__* pagerhist; } ;
struct TYPE_10__ {size_t xnum; int /*<<< orphan*/  continued; } ;
struct TYPE_9__ {size_t bufsize; size_t end; int bufend; int start; char* buffer; int maxsz; } ;
typedef  TYPE_1__ PagerHistoryBuf ;
typedef  TYPE_2__ Line ;
typedef  TYPE_3__ HistoryBuf ;

/* Variables and functions */
 size_t MAX (size_t,size_t) ; 
 int /*<<< orphan*/  init_line (TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 size_t line_as_ansi (TYPE_2__*,char*,int,int*) ; 
 int /*<<< orphan*/  pagerhist_extend (TYPE_1__*,size_t) ; 

__attribute__((used)) static inline void
pagerhist_push(HistoryBuf *self) {
    PagerHistoryBuf *ph = self->pagerhist;
    if (!ph) return;
    bool truncated;
    Line l = {.xnum=self->xnum};
    init_line(self, self->start_of_data, &l);
#define EXPAND_IF_FULL(sz) { \
        if (ph->bufsize - ph->end < sz && !pagerhist_extend(ph, sz)) { \
            ph->bufend = ph->end; ph->end = 0; \
        } \
}
    size_t sz = MAX(1024, ph->bufsize - ph->end);
    sz = MAX(sz, self->xnum + self->xnum);
    EXPAND_IF_FULL(sz);
    if (ph->start != ph->end && !l.continued) {
        ph->buffer[ph->end++] = '\n';
    }
    while(sz < ph->maxsz - 2) {
        size_t num = line_as_ansi(&l, ph->buffer + ph->end, ph->bufsize - ph->end - 2, &truncated);
        if (!truncated) {
            ph->end += num;
            ph->buffer[ph->end++] = '\r';
            if (ph->bufend) {
                ph->start = ph->end + 1 < ph->bufend ? ph->end + 1 : 0;
            }
            break;
        }
        // check if sz is too large too fit in buffer
        if (ph->bufsize > ph->maxsz && !ph->end) break;
        sz *= 2;
        EXPAND_IF_FULL(sz);
    }
#undef EXPAND_IF_FULL
}