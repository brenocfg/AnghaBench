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
struct syscall_desc {int /*<<< orphan*/ * sd_name; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 
 struct syscall_desc* syscalls ; 

__attribute__((used)) static struct syscall_desc *
find_syscall(const char *name)
{
	int i;

	for (i = 0; syscalls[i].sd_name != NULL; i++) {
		if (strcmp(syscalls[i].sd_name, name) == 0)
			return (&syscalls[i]);
	}
	return (NULL);
}