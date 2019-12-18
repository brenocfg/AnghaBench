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
struct cshape {int* shape; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONS_GETCURSORSHAPE ; 
 int /*<<< orphan*/  CONS_SETCURSORSHAPE ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cshape*) ; 
 int /*<<< orphan*/  parse_cursor_params (char*,struct cshape*) ; 
 int /*<<< orphan*/  revert () ; 

__attribute__((used)) static void
set_cursor_type(char *param)
{
	struct cshape shape;

	/* Dry run to determine color, default and local flags. */
	shape.shape[0] = 0;
	shape.shape[1] = -1;
	shape.shape[2] = -1;
	parse_cursor_params(param, &shape);

	/* Get the relevant old setting. */
	if (ioctl(0, CONS_GETCURSORSHAPE, &shape) != 0) {
		revert();
		err(1, "ioctl(CONS_GETCURSORSHAPE)");
	}

	parse_cursor_params(param, &shape);
	if (ioctl(0, CONS_SETCURSORSHAPE, &shape) != 0) {
		revert();
		err(1, "ioctl(CONS_SETCURSORSHAPE)");
	}
}