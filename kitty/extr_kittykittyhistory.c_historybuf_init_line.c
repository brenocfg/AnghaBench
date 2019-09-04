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
typedef  int /*<<< orphan*/  index_type ;
typedef  int /*<<< orphan*/  Line ;
typedef  int /*<<< orphan*/  HistoryBuf ;

/* Variables and functions */
 int /*<<< orphan*/  index_of (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_line (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
historybuf_init_line(HistoryBuf *self, index_type lnum, Line *l) {
    init_line(self, index_of(self, lnum), l);
}