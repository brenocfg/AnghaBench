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
mlx_perform(int unit, void (*func)(int fd, void *arg), void *arg)
{    
    int		fd;
    
    if ((fd = open(ctrlrpath(unit), 0)) >= 0) {
	func(fd, arg);
	close(fd);
    }
}