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
 char next_hfs_char (char const**,size_t*) ; 

__attribute__((used)) static bool verify_dotgit_hfs_generic(const char *path, size_t len, const char *needle, size_t needle_len)
{
	size_t i;
	char c;

	if (next_hfs_char(&path, &len) != '.')
		return true;

	for (i = 0; i < needle_len; i++) {
		c = next_hfs_char(&path, &len);
		if (c != needle[i])
			return true;
	}

	if (next_hfs_char(&path, &len) != '\0')
		return true;

	return false;
}