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
typedef  int /*<<< orphan*/  Screen ;

/* Variables and functions */
 int /*<<< orphan*/  set_mode_from_const (int /*<<< orphan*/ *,unsigned int,int) ; 

void
screen_reset_mode(Screen *self, unsigned int mode) {
    set_mode_from_const(self, mode, false);
}