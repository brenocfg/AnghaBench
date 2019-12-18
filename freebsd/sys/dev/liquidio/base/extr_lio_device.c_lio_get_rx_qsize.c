#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_3__ {int oq; } ;
struct octeon_device {TYPE_2__** droq; TYPE_1__ io_qmask; } ;
struct TYPE_4__ {int max_count; } ;

/* Variables and functions */
 int BIT_ULL (size_t) ; 
 scalar_t__ LIO_MAX_OUTPUT_QUEUES (struct octeon_device*) ; 

int
lio_get_rx_qsize(struct octeon_device *oct, uint32_t q_no)
{

	if ((oct != NULL) && (q_no < (uint32_t)LIO_MAX_OUTPUT_QUEUES(oct)) &&
	    (oct->io_qmask.oq & BIT_ULL(q_no)))
		return (oct->droq[q_no]->max_count);

	return (-1);
}