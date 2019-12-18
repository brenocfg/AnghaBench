#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * heim_isemaphore ;
typedef  int /*<<< orphan*/  heim_ipc ;
struct TYPE_5__ {int /*<<< orphan*/ * data; scalar_t__ length; } ;
typedef  TYPE_1__ heim_idata ;

/* Variables and functions */
 int /*<<< orphan*/  HEIM_IPC_WAIT_FOREVER ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int heim_ipc_async (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int heim_ipc_call (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heim_ipc_free_context (int /*<<< orphan*/ ) ; 
 int heim_ipc_init_context (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * heim_ipc_semaphore_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heim_ipc_semaphore_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reply ; 

__attribute__((used)) static void
test_ipc(const char *service)
{
    heim_isemaphore s;
    heim_idata req, rep;
    heim_ipc ipc;
    int ret;

    ret = heim_ipc_init_context(service, &ipc);
    if (ret)
	errx(1, "heim_ipc_init_context: %d", ret);

    req.length = 0;
    req.data = NULL;

    ret = heim_ipc_call(ipc, &req, &rep, NULL);
    if (ret)
	errx(1, "heim_ipc_call: %d", ret);

    s = heim_ipc_semaphore_create(0);
    if (s == NULL)
	errx(1, "heim_ipc_semaphore_create");

    ret = heim_ipc_async(ipc, &req, s, reply);
    if (ret)
	errx(1, "heim_ipc_async: %d", ret);

    heim_ipc_semaphore_wait(s, HEIM_IPC_WAIT_FOREVER); /* wait for reply to complete the work */

    heim_ipc_free_context(ipc);
}