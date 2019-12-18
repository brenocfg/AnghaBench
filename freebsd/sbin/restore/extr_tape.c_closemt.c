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
 int /*<<< orphan*/  close (scalar_t__) ; 
 scalar_t__ host ; 
 scalar_t__ mt ; 
 int /*<<< orphan*/  pclose (int /*<<< orphan*/ *) ; 
 scalar_t__ pipecmdin ; 
 int /*<<< orphan*/ * popenfp ; 
 int /*<<< orphan*/  rmtclose () ; 

void
closemt(void)
{

	if (mt < 0)
		return;
	if (pipecmdin) {
		pclose(popenfp);
		popenfp = NULL;
	} else
#ifdef RRESTORE
	if (host)
		rmtclose();
	else
#endif
		(void) close(mt);
}