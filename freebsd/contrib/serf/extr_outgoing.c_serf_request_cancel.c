#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* conn; } ;
typedef  TYPE_2__ serf_request_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
struct TYPE_5__ {int /*<<< orphan*/  requests; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_request (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

apr_status_t serf_request_cancel(serf_request_t *request)
{
    return cancel_request(request, &request->conn->requests, 0);
}