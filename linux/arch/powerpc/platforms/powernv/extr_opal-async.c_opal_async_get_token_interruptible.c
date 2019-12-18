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
 int ERESTARTSYS ; 
 int __opal_async_get_token () ; 
 scalar_t__ down_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opal_async_sem ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

int opal_async_get_token_interruptible(void)
{
	int token;

	/* Wait until a token is available */
	if (down_interruptible(&opal_async_sem))
		return -ERESTARTSYS;

	token = __opal_async_get_token();
	if (token < 0)
		up(&opal_async_sem);

	return token;
}