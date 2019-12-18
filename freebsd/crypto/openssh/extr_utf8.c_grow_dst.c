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
 char* recallocarray (char*,size_t,size_t,int) ; 

__attribute__((used)) static int
grow_dst(char **dst, size_t *sz, size_t maxsz, char **dp, size_t need)
{
	char	*tp;
	size_t	 tsz;

	if (*dp + need < *dst + *sz)
		return 0;
	tsz = *sz + 128;
	if (tsz > maxsz)
		tsz = maxsz;
	if ((tp = recallocarray(*dst, *sz, tsz, 1)) == NULL)
		return -1;
	*dp = tp + (*dp - *dst);
	*dst = tp;
	*sz = tsz;
	return 0;
}