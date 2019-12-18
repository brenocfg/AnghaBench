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
 int /*<<< orphan*/  checkfd012 (char*) ; 
 int /*<<< orphan*/  map_init ; 
 int /*<<< orphan*/  stabapply (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
initmaps()
{
#if XDEBUG
	checkfd012("entering initmaps");
#endif /* XDEBUG */
	stabapply(map_init, 0);
#if XDEBUG
	checkfd012("exiting initmaps");
#endif /* XDEBUG */
}