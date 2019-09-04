#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  xnum; int /*<<< orphan*/  count; } ;
struct TYPE_5__ {int /*<<< orphan*/  xnum; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ Line ;
typedef  TYPE_2__ HistoryBuf ;

/* Variables and functions */
 int /*<<< orphan*/  as_text_generic (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl ; 

__attribute__((used)) static PyObject*
as_text(HistoryBuf *self, PyObject *args) {
    Line l = {.xnum=self->xnum};
#define gl(self, y) get_line(self, y, &l);
    as_text_generic(args, self, gl, self->count, self->xnum);
#undef gl
}