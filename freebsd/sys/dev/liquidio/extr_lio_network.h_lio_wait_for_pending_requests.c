#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct octeon_device {TYPE_1__* response_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  pending_req_count; } ;

/* Variables and functions */
 size_t LIO_ORDERED_SC_LIST ; 
 int atomic_load_acq_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lio_sleep_timeout (int) ; 

__attribute__((used)) static inline int
lio_wait_for_pending_requests(struct octeon_device *oct)
{
	int	i, pcount = 0;

	for (i = 0; i < 100; i++) {
		pcount = atomic_load_acq_int(
				     &oct->response_list[LIO_ORDERED_SC_LIST].
					     pending_req_count);
		if (pcount)
			lio_sleep_timeout(100);
		else
			break;
	}

	if (pcount)
		return (1);

	return (0);
}