#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ f_flags; } ;

/* Variables and functions */
 int SOPEN_MAX ; 
 TYPE_1__* files ; 

__attribute__((used)) static int
o_gethandle(void)
{
	int fd;

	for (fd = 0; fd < SOPEN_MAX; fd++)
		if (files[fd].f_flags == 0)
			return (fd);
	return (-1);
}