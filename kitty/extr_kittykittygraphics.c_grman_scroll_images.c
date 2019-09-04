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
struct TYPE_4__ {scalar_t__ has_margins; } ;
typedef  TYPE_1__ ScrollData ;
typedef  int /*<<< orphan*/  GraphicsManager ;
typedef  int /*<<< orphan*/  CellPixelSize ;

/* Variables and functions */
 int /*<<< orphan*/  filter_refs (int /*<<< orphan*/ *,TYPE_1__ const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scroll_filter_func ; 
 int /*<<< orphan*/  scroll_filter_margins_func ; 

void
grman_scroll_images(GraphicsManager *self, const ScrollData *data, CellPixelSize cell) {
    filter_refs(self, data, true, data->has_margins ? scroll_filter_margins_func : scroll_filter_func, cell);
}