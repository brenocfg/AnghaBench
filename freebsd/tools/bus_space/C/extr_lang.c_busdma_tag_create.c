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
typedef  int /*<<< orphan*/  u_int ;
typedef  int busdma_tag_t ;
typedef  int /*<<< orphan*/  bus_size_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int bd_tag_create (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int errno ; 

int
busdma_tag_create(const char *dev, bus_addr_t align, bus_addr_t bndry,
    bus_addr_t maxaddr, bus_size_t maxsz, u_int nsegs, bus_size_t maxsegsz,
    u_int datarate, u_int flags, busdma_tag_t *out_p)
{
	int res;

	res = bd_tag_create(dev, align, bndry, maxaddr, maxsz, nsegs, maxsegsz,
	    datarate, flags);
	if (res == -1)
		return (errno);
	*out_p = res;
	return (0);
}