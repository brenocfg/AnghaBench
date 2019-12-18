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
typedef  int uint64_t ;
struct zfs_probe_args {int secsz; scalar_t__ fd; } ;

/* Variables and functions */
 int vdev_read (int /*<<< orphan*/ *,void*,int,void*,size_t) ; 

__attribute__((used)) static int
zfs_diskread(void *arg, void *buf, size_t blocks, uint64_t offset)
{
	struct zfs_probe_args *ppa;

	ppa = (struct zfs_probe_args *)arg;
	return (vdev_read(NULL, (void *)(uintptr_t)ppa->fd,
	    offset * ppa->secsz, buf, blocks * ppa->secsz));
}