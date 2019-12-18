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
struct iaddr {scalar_t__ len; int* iabuf; } ;

/* Variables and functions */

struct iaddr
subnet_number(struct iaddr addr, struct iaddr mask)
{
	struct iaddr rv;
	unsigned i;

	rv.len = 0;

	/* Both addresses must have the same length... */
	if (addr.len != mask.len)
		return (rv);

	rv.len = addr.len;
	for (i = 0; i < rv.len; i++)
		rv.iabuf[i] = addr.iabuf[i] & mask.iabuf[i];
	return (rv);
}