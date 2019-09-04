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
typedef  int /*<<< orphan*/  GraphicsManager ;
typedef  int /*<<< orphan*/  CellPixelSize ;

/* Variables and functions */
 int /*<<< orphan*/  clear_all_filter_func ; 
 int /*<<< orphan*/  clear_filter_func ; 
 int /*<<< orphan*/  filter_refs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
grman_clear(GraphicsManager *self, bool all, CellPixelSize cell) {
    filter_refs(self, NULL, true, all ? clear_all_filter_func : clear_filter_func, cell);
}