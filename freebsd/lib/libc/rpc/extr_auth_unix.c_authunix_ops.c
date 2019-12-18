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
 int /*<<< orphan*/  authunix_destroy ; 
 int /*<<< orphan*/  authunix_marshal ; 
 int /*<<< orphan*/ * authunix_nextverf ; 
 int /*<<< orphan*/  authunix_refresh ; 
 int /*<<< orphan*/  authunix_validate ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ops_lock ; 

__attribute__((used)) static struct auth_ops *
authunix_ops(void)
{
	static struct auth_ops ops;

	/* VARIABLES PROTECTED BY ops_lock: ops */

	mutex_lock(&ops_lock);
	if (ops.ah_nextverf == NULL) {
		ops.ah_nextverf = authunix_nextverf;
		ops.ah_marshal = authunix_marshal;
		ops.ah_validate = authunix_validate;
		ops.ah_refresh = authunix_refresh;
		ops.ah_destroy = authunix_destroy;
	}
	mutex_unlock(&ops_lock);
	return (&ops);
}