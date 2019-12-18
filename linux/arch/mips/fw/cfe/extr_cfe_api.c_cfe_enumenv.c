#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xiocb_envbuf {int dummy; } ;
struct TYPE_3__ {int enum_idx; int name_length; int val_length; void* val_ptr; void* name_ptr; } ;
struct TYPE_4__ {TYPE_1__ xiocb_envbuf; } ;
struct cfe_xiocb {int xiocb_status; int xiocb_psize; TYPE_2__ plist; scalar_t__ xiocb_flags; scalar_t__ xiocb_handle; int /*<<< orphan*/  xiocb_fcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFE_CMD_ENV_SET ; 
 void* XPTR_FROM_NATIVE (char*) ; 
 int /*<<< orphan*/  cfe_iocb_dispatch (struct cfe_xiocb*) ; 

int cfe_enumenv(int idx, char *name, int namelen, char *val, int vallen)
{
	struct cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_ENV_SET;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handle = 0;
	xiocb.xiocb_flags = 0;
	xiocb.xiocb_psize = sizeof(struct xiocb_envbuf);
	xiocb.plist.xiocb_envbuf.enum_idx = idx;
	xiocb.plist.xiocb_envbuf.name_ptr = XPTR_FROM_NATIVE(name);
	xiocb.plist.xiocb_envbuf.name_length = namelen;
	xiocb.plist.xiocb_envbuf.val_ptr = XPTR_FROM_NATIVE(val);
	xiocb.plist.xiocb_envbuf.val_length = vallen;

	cfe_iocb_dispatch(&xiocb);

	return xiocb.xiocb_status;
}