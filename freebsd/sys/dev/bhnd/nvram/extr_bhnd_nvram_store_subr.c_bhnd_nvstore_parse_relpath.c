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
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 

const char *
bhnd_nvstore_parse_relpath(const char *parent, const char *child)
{
	size_t prefix_len;

	/* All paths have an implicit leading '/'; this allows us to treat
	 * our manufactured root path of "/" as a prefix to all NVRAM-defined
	 * paths (which do not necessarily include a leading '/' */
	if (*parent == '/')
		parent++;

	if (*child == '/')
		child++;

	/* Is parent a prefix of child? */
	prefix_len = strlen(parent);
	if (strncmp(parent, child, prefix_len) != 0)
		return (NULL);

	/* A zero-length prefix matches everything */
	if (prefix_len == 0)
		return (child);

	/* Is child equal to parent? */
	if (child[prefix_len] == '\0')
		return (child + prefix_len);

	/* Is child actually a child of parent? */
	if (child[prefix_len] == '/')
		return (child + prefix_len + 1);

	/* No match (e.g. parent=/foo..., child=/fooo...) */
	return (NULL);
}