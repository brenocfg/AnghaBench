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
typedef  int uint8_t ;
typedef  enum partition_type { ____Placeholder_partition_type } partition_type ;

/* Variables and functions */
#define  FS_BSDFFS 131 
#define  FS_SWAP 130 
#define  FS_VINUM 129 
#define  FS_ZFS 128 
 int PART_FREEBSD_SWAP ; 
 int PART_FREEBSD_UFS ; 
 int PART_FREEBSD_VINUM ; 
 int PART_FREEBSD_ZFS ; 
 int PART_UNKNOWN ; 

__attribute__((used)) static enum partition_type
bsd_parttype(uint8_t type)
{

	switch (type) {
	case FS_SWAP:
		return (PART_FREEBSD_SWAP);
	case FS_BSDFFS:
		return (PART_FREEBSD_UFS);
	case FS_VINUM:
		return (PART_FREEBSD_VINUM);
	case FS_ZFS:
		return (PART_FREEBSD_ZFS);
	}
	return (PART_UNKNOWN);
}