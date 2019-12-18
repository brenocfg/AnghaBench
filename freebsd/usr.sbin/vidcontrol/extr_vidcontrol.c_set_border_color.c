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

/* Variables and functions */
 int /*<<< orphan*/  KDSBORDER ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int get_color_number (char*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  revert () ; 

__attribute__((used)) static void
set_border_color(char *arg)
{
	int color;

	color = get_color_number(arg);
	if (color == -1) {
		revert();
		errx(1, "invalid color '%s'", arg);
	}
	if (ioctl(0, KDSBORDER, color) != 0) {
		revert();
		err(1, "ioctl(KD_SBORDER)");
	}
}