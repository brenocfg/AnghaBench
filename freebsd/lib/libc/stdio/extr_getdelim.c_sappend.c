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
 scalar_t__ expandtofit (char**,size_t,size_t*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 

__attribute__((used)) static int
sappend(char ** __restrict dstp, size_t * __restrict dstlenp,
	size_t * __restrict dstcapp, char * __restrict src, size_t srclen)
{

	/* ensure room for srclen + dstlen + terminating NUL */
	if (expandtofit(dstp, srclen + *dstlenp + 1, dstcapp))
		return (-1);
	memcpy(*dstp + *dstlenp, src, srclen);
	*dstlenp += srclen;
	return (0);
}