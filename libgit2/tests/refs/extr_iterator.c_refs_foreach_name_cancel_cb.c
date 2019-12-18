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
 int /*<<< orphan*/  GIT_UNUSED (char const*) ; 

__attribute__((used)) static int refs_foreach_name_cancel_cb(const char *name, void *payload)
{
	int *cancel_after = payload;
	if (!*cancel_after)
		return -333;
	GIT_UNUSED(name);
	(*cancel_after)--;
	return 0;
}