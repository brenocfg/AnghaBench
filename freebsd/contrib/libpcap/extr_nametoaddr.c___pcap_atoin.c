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
typedef  int u_int ;
typedef  int bpf_u_int32 ;

/* Variables and functions */

int
__pcap_atoin(const char *s, bpf_u_int32 *addr)
{
	u_int n;
	int len;

	*addr = 0;
	len = 0;
	for (;;) {
		n = 0;
		while (*s && *s != '.')
			n = n * 10 + *s++ - '0';
		*addr <<= 8;
		*addr |= n & 0xff;
		len += 8;
		if (*s == '\0')
			return len;
		++s;
	}
	/* NOTREACHED */
}