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
struct smi_info {int msg_flags; } ;

/* Variables and functions */
 int OEM_DATA_AVAIL ; 
 int RECEIVE_MSG_AVAIL ; 

__attribute__((used)) static int oem_data_avail_to_receive_msg_avail(struct smi_info *smi_info)
{
	smi_info->msg_flags = ((smi_info->msg_flags & ~OEM_DATA_AVAIL) |
			       RECEIVE_MSG_AVAIL);
	return 1;
}