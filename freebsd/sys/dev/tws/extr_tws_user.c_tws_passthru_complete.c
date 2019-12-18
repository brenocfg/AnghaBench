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
struct tws_request {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWS_REQ_STATE_COMPLETE ; 
 int /*<<< orphan*/  wakeup_one (struct tws_request*) ; 

void 
tws_passthru_complete(struct tws_request *req)
{
    req->state = TWS_REQ_STATE_COMPLETE;
    wakeup_one(req);

}