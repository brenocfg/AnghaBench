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
typedef  void* u_long ;
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_3__ {void* size; void* base; int /*<<< orphan*/  op; } ;
struct TYPE_4__ {TYPE_1__ sync; } ;
struct proto_ioc_busdma {TYPE_2__ u; int /*<<< orphan*/  key; int /*<<< orphan*/  request; } ;
struct obj {int /*<<< orphan*/  fd; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  ioc ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_TYPE_MD ; 
 int /*<<< orphan*/  PROTO_IOC_BUSDMA ; 
 int /*<<< orphan*/  PROTO_IOC_BUSDMA_SYNC ; 
 int errno ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct proto_ioc_busdma*) ; 
 int /*<<< orphan*/  memset (struct proto_ioc_busdma*,int /*<<< orphan*/ ,int) ; 
 struct obj* obj_lookup (int,int /*<<< orphan*/ ) ; 

int
bd_sync(int mdid, u_int op, u_long ofs, u_long len)
{
	struct proto_ioc_busdma ioc;
	struct obj *md;

	md = obj_lookup(mdid, OBJ_TYPE_MD);
	if (md == NULL)
		return (errno);

	memset(&ioc, 0, sizeof(ioc));
	ioc.request = PROTO_IOC_BUSDMA_SYNC;
	ioc.key = md->key;
	ioc.u.sync.op = op;
	ioc.u.sync.base = ofs;
	ioc.u.sync.size = len;
	if (ioctl(md->fd, PROTO_IOC_BUSDMA, &ioc) == -1)
		return (errno);

	return (0);
}