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
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  VERIEXEC_FILES_FIRST ; 
 int /*<<< orphan*/ * mac_veriexec_metadata_get_file_info (int /*<<< orphan*/ ,long,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
mac_veriexec_metadata_has_file(dev_t fsid, long fileid, unsigned long gen)
{

	return (mac_veriexec_metadata_get_file_info(fsid, fileid, gen, NULL,
	    VERIEXEC_FILES_FIRST) != NULL);
}