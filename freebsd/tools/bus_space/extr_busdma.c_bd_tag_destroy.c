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
struct obj {int refcnt; int /*<<< orphan*/  fd; TYPE_1__* parent; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  ioc ;
struct TYPE_2__ {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  OBJ_TYPE_TAG ; 
 int /*<<< orphan*/  PROTO_IOC_BUSDMA ; 
 int /*<<< orphan*/  PROTO_IOC_BUSDMA_TAG_DESTROY ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int errno ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct proto_ioc_busdma*) ; 
 int /*<<< orphan*/  memset (struct proto_ioc_busdma*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  obj_free (struct obj*) ; 
 struct obj* obj_lookup (int,int /*<<< orphan*/ ) ; 

int
bd_tag_destroy(int tid)
{
	struct proto_ioc_busdma ioc;
	struct obj *ptag, *tag;

	tag = obj_lookup(tid, OBJ_TYPE_TAG);
	if (tag == NULL)
		return (errno);
	if (tag->refcnt > 1)
		return (EBUSY);

	memset(&ioc, 0, sizeof(ioc));
	ioc.request = PROTO_IOC_BUSDMA_TAG_DESTROY;
	ioc.key = tag->key;
	if (ioctl(tag->fd, PROTO_IOC_BUSDMA, &ioc) == -1)
		return (errno);

	if (tag->parent != NULL)
		tag->parent->refcnt--;
	else
		close(tag->fd);
	obj_free(tag);
	return (0);
}