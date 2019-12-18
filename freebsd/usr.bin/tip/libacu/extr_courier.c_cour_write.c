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
 int /*<<< orphan*/  VERBOSE ; 
 scalar_t__ boolean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cour_nap () ; 
 int /*<<< orphan*/  tcdrain (int) ; 
 int /*<<< orphan*/  value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write (int,char*,int) ; 

__attribute__((used)) static void
cour_write(int fd, char *cp, int n)
{
#ifdef notdef
	if (boolean(value(VERBOSE)))
		write(1, cp, n);
#endif
	tcdrain(fd);
	cour_nap();
	for ( ; n-- ; cp++) {
		write(fd, cp, 1);
		tcdrain(fd);
		cour_nap();
	}
}