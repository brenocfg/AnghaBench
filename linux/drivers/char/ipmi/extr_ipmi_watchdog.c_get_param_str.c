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
struct kernel_param {int /*<<< orphan*/  arg; } ;
typedef  int (* action_fn ) (int /*<<< orphan*/ *,char*) ;

/* Variables and functions */
 int strlen (char*) ; 

__attribute__((used)) static int get_param_str(char *buffer, const struct kernel_param *kp)
{
	action_fn fn = (action_fn) kp->arg;
	int       rv;

	rv = fn(NULL, buffer);
	if (rv)
		return rv;
	return strlen(buffer);
}