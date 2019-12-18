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
 int /*<<< orphan*/  O_EXEC ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  _PATH_DEVNULL ; 
 int /*<<< orphan*/  _close (int) ; 
 int _open (char*,int /*<<< orphan*/ ,...) ; 
 int daemonfd (int,int) ; 

int
daemon(int nochdir, int noclose)
{
	int chdirfd, nullfd, ret;

	if (!noclose)
		nullfd = _open(_PATH_DEVNULL, O_RDWR, 0);
	else
		nullfd = -1;

	if (!nochdir)
		chdirfd = _open("/", O_EXEC);
	else
		chdirfd = -1;

	ret = daemonfd(chdirfd, nullfd);

	if (chdirfd != -1)
		_close(chdirfd);

	if (nullfd > 2)
		_close(nullfd);

	return (ret);
}