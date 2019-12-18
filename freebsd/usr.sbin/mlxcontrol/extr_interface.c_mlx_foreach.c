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
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  ctrlrpath (int) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mlx_foreach(void (*func)(int unit, void *arg), void *arg)
{
    int		i, fd;
    
    /* limit total count for sanity */
    for (i = 0; i < 64; i++) {
	/* verify we can open it */
	if ((fd = open(ctrlrpath(i), 0)) >= 0)
	    close(fd);
	/* if we can, do */
	if (fd >= 0) {
	    func(i, arg);
	}
    }
}