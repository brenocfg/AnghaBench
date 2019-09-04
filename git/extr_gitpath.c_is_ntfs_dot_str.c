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
 int is_ntfs_dot_generic (char const*,char const*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static inline int is_ntfs_dot_str(const char *name, const char *dotgit_name,
				  const char *dotgit_ntfs_shortname_prefix)
{
	return is_ntfs_dot_generic(name, dotgit_name, strlen(dotgit_name),
				   dotgit_ntfs_shortname_prefix);
}