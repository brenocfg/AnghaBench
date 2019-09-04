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
 int /*<<< orphan*/  line_attrs ; 
 int /*<<< orphan*/  seg_ptr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline line_attrs_type*
attrptr(HistoryBuf *self, index_type y) {
    seg_ptr(line_attrs, 1);
}