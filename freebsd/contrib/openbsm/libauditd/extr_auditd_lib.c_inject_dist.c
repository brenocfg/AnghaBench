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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static void
inject_dist(const char *fromname, char *toname, size_t tonamesize)
{
	char *ptr;

	ptr = strrchr(fromname, '/');
	assert(ptr != NULL);
	assert(ptr - fromname < (ssize_t)tonamesize);
	strlcpy(toname, fromname, ptr - fromname + 1);
	strlcat(toname, "/dist/", tonamesize);
	strlcat(toname, ptr + 1, tonamesize);
}