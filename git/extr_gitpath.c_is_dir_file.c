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
 scalar_t__ is_dir_sep (char const) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 

__attribute__((used)) static int is_dir_file(const char *buf, const char *dir, const char *file)
{
	int len = strlen(dir);
	if (strncmp(buf, dir, len) || !is_dir_sep(buf[len]))
		return 0;
	while (is_dir_sep(buf[len]))
		len++;
	return !strcmp(buf + len, file);
}