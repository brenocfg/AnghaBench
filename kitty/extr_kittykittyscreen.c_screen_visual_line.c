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
typedef  scalar_t__ index_type ;
struct TYPE_4__ {scalar_t__ lines; } ;
typedef  TYPE_1__ Screen ;
typedef  int /*<<< orphan*/  Line ;

/* Variables and functions */
 int /*<<< orphan*/ * visual_line_ (TYPE_1__*,scalar_t__) ; 

Line*
screen_visual_line(Screen *self, index_type y) {
    if (y >= self->lines) return NULL;
    return visual_line_(self, y);
}