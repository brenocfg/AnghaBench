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

/* Variables and functions */
 int /*<<< orphan*/  clear_target () ; 
 int /*<<< orphan*/  init_ccapi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 () ; 

void
_heim_krb5_ipc_client_clear_target(void)
{
    init_ccapi(NULL);
    if (clear_target != NULL)
        (*clear_target)();
}