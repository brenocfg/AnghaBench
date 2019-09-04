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
typedef  enum prefix_state { ____Placeholder_prefix_state } prefix_state ;

/* Variables and functions */
 int PREFIX_CONTAINS_DIR ; 
 int PREFIX_EXCLUDES_DIR ; 
 int PREFIX_WITHIN_DIR ; 

__attribute__((used)) static enum prefix_state overlaps_prefix(const char *dirname,
					 const char *prefix)
{
	while (*prefix && *dirname == *prefix) {
		dirname++;
		prefix++;
	}
	if (!*prefix)
		return PREFIX_CONTAINS_DIR;
	else if (!*dirname)
		return PREFIX_WITHIN_DIR;
	else
		return PREFIX_EXCLUDES_DIR;
}