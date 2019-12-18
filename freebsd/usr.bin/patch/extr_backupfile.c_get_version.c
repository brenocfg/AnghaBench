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
typedef  enum backup_type { ____Placeholder_backup_type } backup_type ;

/* Variables and functions */
 int argmatch (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  backup_args ; 
 int* backup_types ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  invalid_arg (char*,char const*,int) ; 
 int numbered_existing ; 

enum backup_type
get_version(const char *version)
{
	int	i;

	if (version == NULL || *version == '\0')
		return numbered_existing;
	i = argmatch(version, backup_args);
	if (i >= 0)
		return backup_types[i];
	invalid_arg("version control type", version, i);
	exit(2);
}