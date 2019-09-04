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

int MemorySize(void *ptr)
{
#if defined(WIN32) || defined(_WIN32)
	#ifdef __WATCOMC__
		//Intel 32 bits memory addressing, 16 bytes aligned
	return (_msize(ptr) + 15) >> 4 << 4;
	#else
	return _msize(ptr);
	#endif
#else
	return 0;
#endif
}