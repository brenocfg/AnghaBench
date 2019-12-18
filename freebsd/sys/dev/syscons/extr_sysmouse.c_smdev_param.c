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
struct tty {int dummy; } ;
struct termios {int /*<<< orphan*/  c_ospeed; int /*<<< orphan*/  c_ispeed; } ;

/* Variables and functions */
 int /*<<< orphan*/  B0 ; 
 int /*<<< orphan*/  TTYDEF_SPEED ; 

__attribute__((used)) static int
smdev_param(struct tty *tp, struct termios *t)
{

	/*
	 * Set the output baud rate to zero. The mouse device supports
	 * no output, so we don't want to waste buffers.
	 */
	t->c_ispeed = TTYDEF_SPEED;
	t->c_ospeed = B0;

	return (0);
}