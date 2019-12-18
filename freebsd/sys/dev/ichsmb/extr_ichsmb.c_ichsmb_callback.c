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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int,...) ; 
 int SMB_EABORT ; 
#define  SMB_RELEASE_BUS 129 
#define  SMB_REQUEST_BUS 128 

int 
ichsmb_callback(device_t dev, int index, void *data)
{
	int smb_error = 0;

	DBG("index=%d how=%d\n", index, data ? *(int *)data : -1);
	switch (index) {
	case SMB_REQUEST_BUS:
		break;
	case SMB_RELEASE_BUS:
		break;
	default:
		smb_error = SMB_EABORT;	/* XXX */
		break;
	}
	DBG("smb_error=%d\n", smb_error);
	return (smb_error);
}