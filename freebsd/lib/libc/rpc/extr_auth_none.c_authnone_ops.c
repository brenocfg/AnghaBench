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
struct auth_ops {int /*<<< orphan*/  ah_destroy; int /*<<< orphan*/  ah_refresh; int /*<<< orphan*/  ah_validate; int /*<<< orphan*/  ah_marshal; int /*<<< orphan*/ * ah_nextverf; } ;

/* Variables and functions */
 int /*<<< orphan*/  authnone_destroy ; 
 int /*<<< orphan*/  authnone_marshal ; 
 int /*<<< orphan*/  authnone_refresh ; 
 int /*<<< orphan*/  authnone_validate ; 
 int /*<<< orphan*/ * authnone_verf ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ops_lock ; 

__attribute__((used)) static struct auth_ops *
authnone_ops(void)
{
	static struct auth_ops ops;
 
/* VARIABLES PROTECTED BY ops_lock: ops */
 
	mutex_lock(&ops_lock);
	if (ops.ah_nextverf == NULL) {
		ops.ah_nextverf = authnone_verf;
		ops.ah_marshal = authnone_marshal;
		ops.ah_validate = authnone_validate;
		ops.ah_refresh = authnone_refresh;
		ops.ah_destroy = authnone_destroy;
	}
	mutex_unlock(&ops_lock);
	return (&ops);
}