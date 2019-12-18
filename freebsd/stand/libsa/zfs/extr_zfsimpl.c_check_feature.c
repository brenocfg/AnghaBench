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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/ ** features_for_read ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
check_feature(const char *name, uint64_t value)
{
	int i;

	if (value == 0)
		return (0);
	if (name[0] == '\0')
		return (0);

	for (i = 0; features_for_read[i] != NULL; i++) {
		if (strcmp(name, features_for_read[i]) == 0)
			return (0);
	}
	printf("ZFS: unsupported feature: %s\n", name);
	return (EIO);
}