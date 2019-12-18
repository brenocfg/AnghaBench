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
 int FALSE ; 
 int S_IFDIR ; 
 scalar_t__ stat (char const*,struct stat*) ; 

__attribute__((used)) static int
is_dir(const char *file)
{
	struct stat	sbuf;

	if (stat(file, &sbuf) < 0)
		return (FALSE);

	return (sbuf.st_mode & S_IFDIR);
}