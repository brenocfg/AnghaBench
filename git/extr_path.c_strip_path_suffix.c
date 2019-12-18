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
typedef  int ssize_t ;

/* Variables and functions */
 int stripped_path_suffix_offset (char const*,char const*) ; 
 char* xstrndup (char const*,int) ; 

char *strip_path_suffix(const char *path, const char *suffix)
{
	ssize_t offset = stripped_path_suffix_offset(path, suffix);

	return offset == -1 ? NULL : xstrndup(path, offset);
}