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
 scalar_t__ has_dos_drive_prefix (char const*) ; 
 char* strchr (char const*,char) ; 

int url_is_local_not_ssh(const char *url)
{
	const char *colon = strchr(url, ':');
	const char *slash = strchr(url, '/');
	return !colon || (slash && slash < colon) ||
		has_dos_drive_prefix(url);
}