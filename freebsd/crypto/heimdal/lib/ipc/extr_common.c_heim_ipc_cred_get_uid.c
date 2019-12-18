#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
typedef  TYPE_1__* heim_icred ;
struct TYPE_3__ {int /*<<< orphan*/  uid; } ;

/* Variables and functions */

uid_t
heim_ipc_cred_get_uid(heim_icred cred)
{
    return cred->uid;
}