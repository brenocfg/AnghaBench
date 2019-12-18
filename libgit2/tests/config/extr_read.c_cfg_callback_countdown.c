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
typedef  int /*<<< orphan*/  git_config_entry ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int cfg_callback_countdown(const git_config_entry *entry, void *payload)
{
	int *count = payload;
	GIT_UNUSED(entry);
	(*count)--;
	if (*count == 0)
		return -100;
	return 0;
}