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
struct pidfh {int pf_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDOOFUS ; 
 int /*<<< orphan*/  errno ; 

int
pidfile_fileno(const struct pidfh *pfh)
{

	if (pfh == NULL || pfh->pf_fd == -1) {
		errno = EDOOFUS;
		return (-1);
	}
	return (pfh->pf_fd);
}