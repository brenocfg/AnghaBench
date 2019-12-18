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
struct request {int /*<<< orphan*/  tag; } ;
struct driver_data {TYPE_1__* port; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmds_to_issue; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_abort_request (struct request*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool mtip_queue_cmd(struct request *req, void *data, bool reserved)
{
	struct driver_data *dd = data;

	set_bit(req->tag, dd->port->cmds_to_issue);
	blk_abort_request(req);
	return true;
}