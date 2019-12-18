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
typedef  scalar_t__ int16_t ;
struct TYPE_4__ {scalar_t__ x; scalar_t__ width; } ;
typedef  TYPE_1__ button_t ;

/* Variables and functions */
 int buttoncnt ; 
 TYPE_1__* buttons ; 

__attribute__((used)) static button_t *get_button_at(int16_t x, int16_t y) {
    for (int c = 0; c < buttoncnt; c++)
        if (x >= (buttons[c].x) && x <= (buttons[c].x + buttons[c].width))
            return &buttons[c];

    return NULL;
}