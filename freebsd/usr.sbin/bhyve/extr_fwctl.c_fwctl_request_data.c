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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int req_size; TYPE_1__* req_op; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* op_data ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  fwctl_request_done () ; 
 TYPE_2__ rinfo ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
fwctl_request_data(uint32_t value)
{

	/* Make sure remaining size is >= 0 */
	if (rinfo.req_size <= sizeof(uint32_t))
		rinfo.req_size = 0;
	else
		rinfo.req_size -= sizeof(uint32_t);

	(*rinfo.req_op->op_data)(value, rinfo.req_size);

	if (rinfo.req_size < sizeof(uint32_t)) {
		fwctl_request_done();
		return (1);
	}

	return (0);
}