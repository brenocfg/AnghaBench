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
typedef  int uint32_t ;

/* Variables and functions */
 int UINT_MAX ; 
 int getpid () ; 
 int* used_ports_map ; 

__attribute__((used)) static uint32_t generate_local_port(void)
{
	int i, n;
	uint32_t pid = getpid() & 0x3FFFFF;

	for (i = 0; i < 32; i++) {
		if (used_ports_map[i] == 0xFFFFFFFF)
			continue;

		for (n = 0; n < 32; n++) {
			if (1UL & (used_ports_map[i] >> n))
				continue;

			used_ports_map[i] |= (1UL << n);
			n += (i * 32);

			/* PID_MAX_LIMIT is currently at 2^22, leaving 10 bit
			 * to, i.e. 1024 unique ports per application. */
			return pid + (n << 22);

		}
	}

	/* Out of sockets in our own PID namespace, what to do? FIXME */
	return UINT_MAX;
}