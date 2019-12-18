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
typedef  int /*<<< orphan*/  uid_t ;

/* Variables and functions */
 int /*<<< orphan*/  init_ccapi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_target_uid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void
_heim_krb5_ipc_client_set_target_uid(uid_t uid)
{
    init_ccapi(NULL);
    if (set_target_uid != NULL)
        (*set_target_uid)(uid);
}