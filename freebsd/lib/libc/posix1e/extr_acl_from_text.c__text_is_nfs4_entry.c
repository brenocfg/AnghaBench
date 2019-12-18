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
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int
_text_is_nfs4_entry(const char *entry)
{
	int count = 0;

	assert(strlen(entry) > 0);

	while (*entry != '\0') {
		if (*entry == ':' || *entry == '@')
			count++;
		entry++;
	}

	if (count <= 2)
		return (0);

	return (1);
}