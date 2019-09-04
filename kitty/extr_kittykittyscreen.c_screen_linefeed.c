#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ mLNM; } ;
struct TYPE_9__ {TYPE_1__ modes; } ;
typedef  TYPE_2__ Screen ;

/* Variables and functions */
 int cursor_within_margins (TYPE_2__*) ; 
 int /*<<< orphan*/  screen_carriage_return (TYPE_2__*) ; 
 int /*<<< orphan*/  screen_ensure_bounds (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  screen_index (TYPE_2__*) ; 

void
screen_linefeed(Screen *self) {
    bool in_margins = cursor_within_margins(self);
    screen_index(self);
    if (self->modes.mLNM) screen_carriage_return(self);
    screen_ensure_bounds(self, false, in_margins);
}