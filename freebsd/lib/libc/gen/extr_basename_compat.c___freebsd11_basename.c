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
 int /*<<< orphan*/  MAXPATHLEN ; 
 char* __freebsd11_basename_r (char*,char*) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 

char *
__freebsd11_basename(char *path)
{
	static char *bname = NULL;

	if (bname == NULL) {
		bname = (char *)malloc(MAXPATHLEN);
		if (bname == NULL)
			return (NULL);
	}
	return (__freebsd11_basename_r(path, bname));
}