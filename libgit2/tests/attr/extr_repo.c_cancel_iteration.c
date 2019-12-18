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
 int CANCEL_VALUE ; 
 int /*<<< orphan*/  GIT_UNUSED (char const*) ; 

__attribute__((used)) static int cancel_iteration(
	const char *name,
	const char *value,
	void *payload)
{
	GIT_UNUSED(name);
	GIT_UNUSED(value);

	*((int *)payload) -= 1;

	if (*((int *)payload) < 0)
		return CANCEL_VALUE;

	return 0;
}