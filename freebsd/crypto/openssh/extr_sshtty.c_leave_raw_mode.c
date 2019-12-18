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
 int /*<<< orphan*/  TCSADRAIN ; 
 scalar_t__ _in_raw_mode ; 
 int /*<<< orphan*/  _saved_tio ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stdin ; 
 int tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
leave_raw_mode(int quiet)
{
	if (!_in_raw_mode)
		return;
	if (tcsetattr(fileno(stdin), TCSADRAIN, &_saved_tio) == -1) {
		if (!quiet)
			perror("tcsetattr");
	} else
		_in_raw_mode = 0;
}