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
 int O_LARGEFILE ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  _PATH_DEVNULL ; 
 int /*<<< orphan*/  dcopy (int,int) ; 
 scalar_t__ didfds ; 
 int /*<<< orphan*/  dmove (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xclose (int) ; 
 int xopen (int /*<<< orphan*/ ,int) ; 

void
donefds(void)
{

    xclose(0);
    xclose(1);
    xclose(2);
    didfds = 0;
#ifdef NISPLUS
    {
	int fd = xopen(_PATH_DEVNULL, O_RDONLY|O_LARGEFILE);
	(void)dcopy(fd, 1);
	(void)dcopy(fd, 2);
	(void)dmove(fd, 0);
    }
#endif /*NISPLUS*/    
}