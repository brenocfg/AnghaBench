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
 int _citrus_esdb_get_list (char***,size_t*,int) ; 
 int errno ; 

int
__bsd___iconv_get_list(char ***rlist, size_t *rsz, bool sorted)
{
	int ret;

	ret = _citrus_esdb_get_list(rlist, rsz, sorted);
	if (ret) {
		errno = ret;
		return (-1);
	}

	return (0);
}