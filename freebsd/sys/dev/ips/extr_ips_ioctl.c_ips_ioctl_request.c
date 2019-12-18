#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct TYPE_7__ {int /*<<< orphan*/  command_buffer; } ;
typedef  TYPE_1__ ips_user_request ;
typedef  int /*<<< orphan*/  ips_softc_t ;
struct TYPE_8__ {int readwrite; struct TYPE_8__* command_buffer; int /*<<< orphan*/  datasize; } ;
typedef  TYPE_2__ ips_ioctl_t ;
typedef  int /*<<< orphan*/  ips_generic_cmd ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IPS_IOCTL_BUFFER_SIZE ; 
 int IPS_IOCTL_READ ; 
 int IPS_IOCTL_WRITE ; 
#define  IPS_USER_CMD 128 
 int /*<<< orphan*/  M_IPSBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  copyin (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int ips_ioctl_cmd (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*) ; 
 void* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ips_ioctl_request(ips_softc_t *sc, u_long ioctl_request, caddr_t addr, int32_t flags){
	int error = EINVAL;
	ips_ioctl_t *ioctl_cmd;
	ips_user_request *user_request;
	switch(ioctl_request){
	case IPS_USER_CMD:
		user_request = (ips_user_request *)addr;
		ioctl_cmd = malloc(sizeof(ips_ioctl_t), M_IPSBUF, M_WAITOK);
		ioctl_cmd->command_buffer = malloc(sizeof(ips_generic_cmd),
						M_IPSBUF, M_WAITOK);
		if(copyin(user_request->command_buffer, 
		    ioctl_cmd->command_buffer, sizeof(ips_generic_cmd))){
			free(ioctl_cmd->command_buffer, M_IPSBUF);
			free(ioctl_cmd, M_IPSBUF);
			break;
		}
		ioctl_cmd->readwrite = IPS_IOCTL_READ | IPS_IOCTL_WRITE;
		ioctl_cmd->datasize = IPS_IOCTL_BUFFER_SIZE;
		error = ips_ioctl_cmd(sc, ioctl_cmd, user_request);
		free(ioctl_cmd->command_buffer, M_IPSBUF);
		free(ioctl_cmd, M_IPSBUF);
		break;
	}

	return error;
}