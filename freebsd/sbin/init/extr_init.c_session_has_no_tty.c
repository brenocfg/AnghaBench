#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int se_flags; int /*<<< orphan*/  se_device; } ;
typedef  TYPE_1__ session_t ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int SE_IFCONSOLE ; 
 int SE_IFEXISTS ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int open (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
session_has_no_tty(session_t *sp)
{
	int fd;

	if ((sp->se_flags & SE_IFEXISTS) == 0 &&
	    (sp->se_flags & SE_IFCONSOLE) == 0)
		return (0);

	fd = open(sp->se_device, O_RDONLY | O_NONBLOCK, 0);
	if (fd < 0) {
		if (errno == ENOENT)
			return (1);
		return (0);
	}

	close(fd);
	return (0);
}