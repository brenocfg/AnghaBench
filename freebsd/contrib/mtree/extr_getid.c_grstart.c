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
 scalar_t__ _gr_filesdone ; 
 int /*<<< orphan*/ * _gr_fp ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 char* grfile ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

__attribute__((used)) static int
grstart(void)
{

	_gr_filesdone = 0;
	if (_gr_fp) {
		rewind(_gr_fp);
		return 1;
	}
	if (grfile[0] == '\0')			/* sanity check */
		return 0;

	_gr_fp = fopen(grfile, "r");
	if (_gr_fp != NULL)
		return 1;
	warn("Can't open `%s'", grfile);
	return 0;
}