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
 int /*<<< orphan*/  F_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 char* realpath (char const*,char*) ; 

char *p_realpath(const char *pathname, char *resolved)
{
	char *ret;
	if ((ret = realpath(pathname, resolved)) == NULL)
		return NULL;

#ifdef __OpenBSD__
	/* The OpenBSD realpath function behaves differently,
	 * figure out if the file exists */
	if (access(ret, F_OK) < 0)
		ret = NULL;
#endif
	return ret;
}