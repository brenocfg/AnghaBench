#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_2__ {int os_dnodesize; } ;
typedef  TYPE_1__ objset_t ;

/* Variables and functions */
 int DNODE_MIN_SIZE ; 
#define  ZFS_DNSIZE_16K 134 
#define  ZFS_DNSIZE_1K 133 
#define  ZFS_DNSIZE_2K 132 
#define  ZFS_DNSIZE_4K 131 
#define  ZFS_DNSIZE_8K 130 
#define  ZFS_DNSIZE_AUTO 129 
#define  ZFS_DNSIZE_LEGACY 128 

__attribute__((used)) static void
dnodesize_changed_cb(void *arg, uint64_t newval)
{
	objset_t *os = arg;

	switch (newval) {
	case ZFS_DNSIZE_LEGACY:
		os->os_dnodesize = DNODE_MIN_SIZE;
		break;
	case ZFS_DNSIZE_AUTO:
		/*
		 * Choose a dnode size that will work well for most
		 * workloads if the user specified "auto". Future code
		 * improvements could dynamically select a dnode size
		 * based on observed workload patterns.
		 */
		os->os_dnodesize = DNODE_MIN_SIZE * 2;
		break;
	case ZFS_DNSIZE_1K:
	case ZFS_DNSIZE_2K:
	case ZFS_DNSIZE_4K:
	case ZFS_DNSIZE_8K:
	case ZFS_DNSIZE_16K:
		os->os_dnodesize = newval;
		break;
	}
}