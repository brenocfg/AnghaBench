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
typedef  int /*<<< orphan*/  LineBuf ;
typedef  int /*<<< orphan*/  HistoryBuf ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 int /*<<< orphan*/ * alloc_linebuf (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  linebuf_rewrap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline LineBuf*
realloc_lb(LineBuf *old, unsigned int lines, unsigned int columns, index_type *nclb, index_type *ncla, HistoryBuf *hb, index_type *x, index_type *y) {
    LineBuf *ans = alloc_linebuf(lines, columns);
    if (ans == NULL) { PyErr_NoMemory(); return NULL; }
    linebuf_rewrap(old, ans, nclb, ncla, hb, x, y);
    return ans;
}