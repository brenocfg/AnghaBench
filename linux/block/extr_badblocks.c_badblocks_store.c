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
struct badblocks {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t ENOSPC ; 
 scalar_t__ badblocks_set (struct badblocks*,unsigned long long,int,int) ; 
 int sscanf (char const*,char*,unsigned long long*,int*,char*) ; 

ssize_t badblocks_store(struct badblocks *bb, const char *page, size_t len,
			int unack)
{
	unsigned long long sector;
	int length;
	char newline;

	switch (sscanf(page, "%llu %d%c", &sector, &length, &newline)) {
	case 3:
		if (newline != '\n')
			return -EINVAL;
		/* fall through */
	case 2:
		if (length <= 0)
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}

	if (badblocks_set(bb, sector, length, !unack))
		return -ENOSPC;
	else
		return len;
}