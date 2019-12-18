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
struct termios {int /*<<< orphan*/  c_ospeed; int /*<<< orphan*/  c_ispeed; } ;
typedef  int /*<<< orphan*/  speed_t ;

/* Variables and functions */

int
cfsetspeed(struct termios *t, speed_t speed)
{

	t->c_ispeed = t->c_ospeed = speed;
	return (0);
}