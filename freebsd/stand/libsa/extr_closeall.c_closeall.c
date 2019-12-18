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
 int /*<<< orphan*/  close (int) ; 
 TYPE_1__* files ; 

void
closeall()
{
	int i;

        for (i = 0; i < SOPEN_MAX; i++)
            if (files[i].f_flags != 0)
                (void)close(i);
}