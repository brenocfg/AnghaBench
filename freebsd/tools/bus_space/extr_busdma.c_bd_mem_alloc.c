#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_5__ {int phys_nsegs; int bus_nsegs; uintptr_t phys_addr; uintptr_t bus_addr; int /*<<< orphan*/  flags; int /*<<< orphan*/  tag; } ;
struct TYPE_6__ {TYPE_1__ md; } ;
struct proto_ioc_busdma {int /*<<< orphan*/  key; int /*<<< orphan*/  request; TYPE_2__ u; int /*<<< orphan*/  result; } ;
struct TYPE_7__ {int /*<<< orphan*/  maxsz; } ;
struct TYPE_8__ {TYPE_3__ tag; } ;
struct obj {int refcnt; int oid; struct obj* parent; int /*<<< orphan*/  fd; int /*<<< orphan*/  key; TYPE_4__ u; } ;
typedef  int /*<<< orphan*/  ioc ;

/* Variables and functions */
 int /*<<< orphan*/  BUSDMA_MD_BUS ; 
 int /*<<< orphan*/  BUSDMA_MD_PHYS ; 
 int /*<<< orphan*/  BUSDMA_MD_VIRT ; 
 scalar_t__ MAP_FAILED ; 
 int MAP_NOCORE ; 
 int MAP_SHARED ; 
 int /*<<< orphan*/  OBJ_TYPE_MD ; 
 int /*<<< orphan*/  OBJ_TYPE_TAG ; 
 int /*<<< orphan*/  PROTO_IOC_BUSDMA ; 
 int /*<<< orphan*/  PROTO_IOC_BUSDMA_MEM_ALLOC ; 
 int /*<<< orphan*/  PROTO_IOC_BUSDMA_MEM_FREE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 int bd_md_add_seg (struct obj*,int /*<<< orphan*/ ,uintptr_t,int /*<<< orphan*/ ) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct proto_ioc_busdma*) ; 
 int /*<<< orphan*/  memset (struct proto_ioc_busdma*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,uintptr_t) ; 
 struct obj* obj_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obj_free (struct obj*) ; 
 struct obj* obj_lookup (int,int /*<<< orphan*/ ) ; 

int
bd_mem_alloc(int tid, u_int flags)
{
	struct proto_ioc_busdma ioc;
	struct obj *md, *tag;
	uintptr_t addr;
	int error;

	tag = obj_lookup(tid, OBJ_TYPE_TAG);
	if (tag == NULL)
		return (-1);

	md = obj_alloc(OBJ_TYPE_MD);
	if (md == NULL)
		return (-1);

	memset(&ioc, 0, sizeof(ioc));
	ioc.request = PROTO_IOC_BUSDMA_MEM_ALLOC;
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

	/* XXX we need to support multiple segments */
	assert(ioc.u.md.phys_nsegs == 1);
	assert(ioc.u.md.bus_nsegs == 1);
	error = bd_md_add_seg(md, BUSDMA_MD_PHYS, ioc.u.md.phys_addr,
	    tag->u.tag.maxsz);
	error = bd_md_add_seg(md, BUSDMA_MD_BUS, ioc.u.md.bus_addr,
	    tag->u.tag.maxsz);

	addr = (uintptr_t)mmap(NULL, tag->u.tag.maxsz, PROT_READ | PROT_WRITE,
	    MAP_NOCORE | MAP_SHARED, md->fd, ioc.u.md.phys_addr);
	if (addr == (uintptr_t)MAP_FAILED)
		goto fail;
	error = bd_md_add_seg(md, BUSDMA_MD_VIRT, addr, tag->u.tag.maxsz);

	return (md->oid);

 fail:
	memset(&ioc, 0, sizeof(ioc));
	ioc.request = PROTO_IOC_BUSDMA_MEM_FREE;
	ioc.key = md->key;
	ioctl(md->fd, PROTO_IOC_BUSDMA, &ioc);
	md->parent->refcnt--;
	obj_free(md);
	return (-1);
}