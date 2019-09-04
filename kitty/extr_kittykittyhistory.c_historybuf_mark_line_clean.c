#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  line_attrs_type ;
typedef  int /*<<< orphan*/  index_type ;
typedef  int /*<<< orphan*/  HistoryBuf ;

/* Variables and functions */
 int /*<<< orphan*/  TEXT_DIRTY_MASK ; 
 int /*<<< orphan*/ * attrptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_of (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
historybuf_mark_line_clean(HistoryBuf *self, index_type y) {
    line_attrs_type *p = attrptr(self, index_of(self, y));
    *p &= ~TEXT_DIRTY_MASK;
}