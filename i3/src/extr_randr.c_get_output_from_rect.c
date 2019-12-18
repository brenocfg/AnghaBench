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
struct TYPE_4__ {int x; int width; int y; int height; } ;
typedef  TYPE_1__ Rect ;
typedef  int /*<<< orphan*/  Output ;

/* Variables and functions */
 int /*<<< orphan*/ * get_output_containing (unsigned int,unsigned int) ; 
 int /*<<< orphan*/ * output_containing_rect (TYPE_1__) ; 

Output *get_output_from_rect(Rect rect) {
    unsigned int mid_x = rect.x + rect.width / 2;
    unsigned int mid_y = rect.y + rect.height / 2;
    Output *output = get_output_containing(mid_x, mid_y);

    return output ? output : output_containing_rect(rect);
}