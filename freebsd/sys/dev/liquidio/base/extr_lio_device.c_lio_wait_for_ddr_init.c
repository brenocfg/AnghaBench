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
typedef  unsigned long uint32_t ;
struct octeon_device {int dummy; } ;

/* Variables and functions */
 int lio_mem_access_ok (struct octeon_device*) ; 
 int /*<<< orphan*/  lio_sleep_timeout (int) ; 

int
lio_wait_for_ddr_init(struct octeon_device *oct, unsigned long *timeout)
{
	int		ret = 1;
	uint32_t	ms;

	if (timeout == NULL)
		return (ret);

	for (ms = 0; ret && ((*timeout == 0) || (ms <= *timeout)); ms += 100) {
		ret = lio_mem_access_ok(oct);

		/* wait 100 ms */
		if (ret)
			lio_sleep_timeout(100);
	}

	return (ret);
}