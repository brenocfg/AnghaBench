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
 int /*<<< orphan*/  curinode ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
checkactive(void)
{
    if (!curinode) {
	warnx("no current inode\n");
	return 0;
    }
    return 1;
}