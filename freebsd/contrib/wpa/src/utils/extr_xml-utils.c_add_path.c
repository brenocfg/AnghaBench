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
 char* os_malloc (size_t) ; 
 int /*<<< orphan*/  os_snprintf (char*,size_t,char*,char const*,char const*) ; 
 int os_strlen (char const*) ; 

__attribute__((used)) static char * add_path(const char *prev, const char *leaf)
{
	size_t len;
	char *new_uri;

	if (prev == NULL)
		return NULL;

	len = os_strlen(prev) + 1 + os_strlen(leaf) + 1;
	new_uri = os_malloc(len);
	if (new_uri)
		os_snprintf(new_uri, len, "%s/%s", prev, leaf);

	return new_uri;
}