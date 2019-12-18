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
struct mps_usr_command {int dummy; } ;
struct mps_user_func {int (* f_pre ) (struct mps_command*,struct mps_usr_command*) ;scalar_t__ Function; } ;
struct mps_command {scalar_t__ cm_req; } ;
struct TYPE_2__ {scalar_t__ Function; } ;
typedef  TYPE_1__ MPI2_REQUEST_HEADER ;

/* Variables and functions */
 int EINVAL ; 
 struct mps_user_func* mps_user_func_list ; 
 int stub1 (struct mps_command*,struct mps_usr_command*) ; 

__attribute__((used)) static int
mps_user_setup_request(struct mps_command *cm, struct mps_usr_command *cmd)
{
	MPI2_REQUEST_HEADER *hdr = (MPI2_REQUEST_HEADER *)cm->cm_req;	
	struct mps_user_func *f;

	for (f = mps_user_func_list; f->f_pre != NULL; f++) {
		if (hdr->Function == f->Function)
			return (f->f_pre(cm, cmd));
	}
	return (EINVAL);
}