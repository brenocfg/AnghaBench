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
typedef  union ctl_io {int dummy; } ctl_io ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_HA_DT_CMD_WRITE ; 
 int /*<<< orphan*/  ctl_datamove_remote_write_cb ; 
 int ctl_datamove_remote_xfer (union ctl_io*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ctl_datamove_remote_dm_write_cb(union ctl_io *io)
{
	int retval;

	retval = ctl_datamove_remote_xfer(io, CTL_HA_DT_CMD_WRITE,
					  ctl_datamove_remote_write_cb);
	return (retval);
}