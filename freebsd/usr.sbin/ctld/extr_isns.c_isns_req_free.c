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
struct isns_req {struct isns_req* ir_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct isns_req*) ; 

void
isns_req_free(struct isns_req *req)
{

	free(req->ir_buf);
	free(req);
}