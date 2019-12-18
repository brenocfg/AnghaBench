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
 int chdir (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* xmemdupz (char const*,int) ; 

__attribute__((used)) static int chdir_len(const char *orig, int len)
{
	char *path = xmemdupz(orig, len);
	int r = chdir(path);
	free(path);
	return r;
}