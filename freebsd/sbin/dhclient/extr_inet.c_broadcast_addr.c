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
struct iaddr {unsigned int len; int* iabuf; } ;

/* Variables and functions */

struct iaddr
broadcast_addr(struct iaddr subnet, struct iaddr mask)
{
	struct iaddr rv;
	unsigned i;

	if (subnet.len != mask.len) {
		rv.len = 0;
		return (rv);
	}

	for (i = 0; i < subnet.len; i++)
		rv.iabuf[i] = subnet.iabuf[i] | (~mask.iabuf[i] & 255);
	rv.len = subnet.len;

	return (rv);
}