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
struct stat {int st_mode; } ;

/* Variables and functions */
 int S_IFCHR ; 
 int S_IFMT ; 
 scalar_t__ stat (char*,struct stat*) ; 

char *
rawname(char *cp)
{
	struct stat sb;

	/*
	 * Ensure that the device passed in is a raw device.
	 */
	if (stat(cp, &sb) == 0 && (sb.st_mode & S_IFMT) == S_IFCHR)
		return (cp);

	/*
	 * Since there's only one device type now, we can't construct any
	 * better name, so we have to return NULL.
	 */
	return (NULL);
}