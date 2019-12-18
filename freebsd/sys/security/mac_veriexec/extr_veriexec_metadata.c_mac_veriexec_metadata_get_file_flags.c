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
struct mac_veriexec_file_info {int flags; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int ENOENT ; 
 struct mac_veriexec_file_info* mac_veriexec_metadata_get_file_info (int /*<<< orphan*/ ,long,unsigned long,int*,int) ; 

int
mac_veriexec_metadata_get_file_flags(dev_t fsid, long fileid, unsigned long gen,
    int *flags, int check_files)
{
	struct mac_veriexec_file_info *ip;
	int found_dev;

	ip = mac_veriexec_metadata_get_file_info(fsid, fileid, gen, &found_dev,
	    check_files);
	if (ip == NULL)
		return (ENOENT);

	*flags = ip->flags;
	return (0);
}