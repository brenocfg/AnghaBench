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
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int /*<<< orphan*/  efunc (int,char*,size_t,size_t) ; 
 int /*<<< orphan*/  errno ; 
 size_t strlcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  stub1 (int,char*,size_t,size_t) ; 

size_t
estrlcpy(char *dst, const char *src, size_t len)
{
	size_t rv;
	if ((rv = strlcpy(dst, src, len)) >= len) {
		errno = ENAMETOOLONG;
		(*efunc)(1,
		    "Cannot copy string; %zu chars needed %zu provided",
		    rv, len);
	}
	return rv;
}