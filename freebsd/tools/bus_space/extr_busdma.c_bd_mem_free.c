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
struct proto_ioc_busdma {int /*<<< orphan*/  key; int /*<<< orphan*/  request; } ;
struct obj {TYPE_1__* parent; int /*<<< orphan*/  fd; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  ioc ;
struct TYPE_2__ {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUSDMA_MD_BUS ; 
 int /*<<< orphan*/  BUSDMA_MD_PHYS ; 
 int /*<<< orphan*/  BUSDMA_MD_VIRT ; 
 int /*<<< orphan*/  OBJ_TYPE_MD ; 
 int /*<<< orphan*/  PROTO_IOC_BUSDMA ; 
 int /*<<< orphan*/  PROTO_IOC_BUSDMA_MEM_FREE ; 
 int /*<<< orphan*/  bd_md_del_segs (struct obj*,int /*<<< orphan*/ ,int) ; 
 int errno ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct proto_ioc_busdma*) ; 
 int /*<<< orphan*/  memset (struct proto_ioc_busdma*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  obj_free (struct obj*) ; 
 struct obj* obj_lookup (int,int /*<<< orphan*/ ) ; 

int
bd_mem_free(int mdid)
{
	struct proto_ioc_busdma ioc;
	struct obj *md;

	md = obj_lookup(mdid, OBJ_TYPE_MD);
	if (md == NULL)
		return (errno);

	memset(&ioc, 0, sizeof(ioc));
	ioc.request = PROTO_IOC_BUSDMA_MEM_FREE;
	ioc.key = md->key;
	if (ioctl(md->fd, PROTO_IOC_BUSDMA, &ioc) == -1)
		return (errno);

	bd_md_del_segs(md, BUSDMA_MD_VIRT, 1);
	bd_md_del_segs(md, BUSDMA_MD_PHYS, 0);
	bd_md_del_segs(md, BUSDMA_MD_BUS, 0);
	md->parent->refcnt--;
	obj_free(md);
	return (0);
}