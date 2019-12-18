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
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_3__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  tag; } ;
struct TYPE_4__ {TYPE_1__ md; } ;
struct proto_ioc_busdma {int /*<<< orphan*/  result; TYPE_2__ u; int /*<<< orphan*/  request; } ;
struct obj {int refcnt; int oid; int /*<<< orphan*/  key; struct obj* parent; int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/  ioc ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_TYPE_MD ; 
 int /*<<< orphan*/  OBJ_TYPE_TAG ; 
 int /*<<< orphan*/  PROTO_IOC_BUSDMA ; 
 int /*<<< orphan*/  PROTO_IOC_BUSDMA_MD_CREATE ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct proto_ioc_busdma*) ; 
 int /*<<< orphan*/  memset (struct proto_ioc_busdma*,int /*<<< orphan*/ ,int) ; 
 struct obj* obj_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obj_free (struct obj*) ; 
 struct obj* obj_lookup (int,int /*<<< orphan*/ ) ; 

int
bd_md_create(int tid, u_int flags)
{
	struct proto_ioc_busdma ioc;
	struct obj *md, *tag;

	tag = obj_lookup(tid, OBJ_TYPE_TAG);
	if (tag == NULL)
		return (-1);

	md = obj_alloc(OBJ_TYPE_MD);
	if (md == NULL)
		return (-1);

	memset(&ioc, 0, sizeof(ioc));
	ioc.request = PROTO_IOC_BUSDMA_MD_CREATE;
	ioc.u.md.tag = tag->key;
	ioc.u.md.flags = flags;
	if (ioctl(tag->fd, PROTO_IOC_BUSDMA, &ioc) == -1) {
		obj_free(md);
		return (-1);
	}

	md->refcnt = 1;
	md->fd = tag->fd;
	md->parent = tag;
	tag->refcnt++;
	md->key = ioc.result;
	return (md->oid);
}