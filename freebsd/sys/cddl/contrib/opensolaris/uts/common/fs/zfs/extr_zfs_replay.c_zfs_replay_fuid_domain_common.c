#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void** z_domain_table; } ;
typedef  TYPE_1__ zfs_fuid_info_t ;
typedef  int caddr_t ;

/* Variables and functions */
 void* strlen (void*) ; 

__attribute__((used)) static void *
zfs_replay_fuid_domain_common(zfs_fuid_info_t *fuid_infop, void *start,
    int domcnt)
{
	int i;

	for (i = 0; i != domcnt; i++) {
		fuid_infop->z_domain_table[i] = start;
		start = (caddr_t)start + strlen(start) + 1;
	}

	return (start);
}