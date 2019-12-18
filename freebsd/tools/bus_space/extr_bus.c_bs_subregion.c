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
struct resource {long size; int fd; long addr; long ofs; int rid; void* ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  errno ; 
 int rid_alloc () ; 
 struct resource* rid_lookup (int) ; 

int
bs_subregion(int rid0, long ofs, long sz)
{
	struct resource *r;
	void *ptr0;
	long addr0, ofs0;
	int fd0, rid;

	r = rid_lookup(rid0);
	if (r == NULL)
		return (-1);
	if (ofs < 0 || sz < 1) {
		errno = EINVAL;
		return (-1);
	}
	if (ofs + sz > r->size) {
		errno = ENOSPC;
		return (-1);
	}
	fd0 = r->fd;
	addr0 = r->addr;
	ofs0 = r->ofs;
	ptr0 = r->ptr;
	rid = rid_alloc();
	if (rid == -1)
		return (-1);
	r = rid_lookup(rid);
	if (r == NULL)
		return (-1);
	r->rid = rid0;
	r->fd = fd0;
	r->addr = addr0 + ofs;
	r->size = sz;
	r->ofs = ofs0 + ofs;
	r->ptr = ptr0;
	return (rid);
}