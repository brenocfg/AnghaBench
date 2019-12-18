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
 int /*<<< orphan*/  WSACleanup () ; 
 int /*<<< orphan*/  smiExit () ; 

void
nd_cleanup(void)
{
#ifdef USE_LIBSMI
	/*
	 * This appears, in libsmi 0.4.8, to do nothing if smiInit()
	 * wasn't done or failed, so we call it unconditionally.
	 */
	smiExit();
#endif

#ifdef _WIN32
	/*
	 * Undo the WSAStartup() call above.
	 */
	WSACleanup();
#endif
}