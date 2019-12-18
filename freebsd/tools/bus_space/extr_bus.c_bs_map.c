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
struct resource {int fd; int rid; scalar_t__ ofs; int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; int /*<<< orphan*/  addr; } ;
struct proto_ioc_region {int /*<<< orphan*/  size; int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int MAP_NOCORE ; 
 int MAP_SHARED ; 
 int /*<<< orphan*/  O_RDWR ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  PROTO_IOC_REGION ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int ioctl (int,int /*<<< orphan*/ ,struct proto_ioc_region*) ; 
 int /*<<< orphan*/  mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,scalar_t__) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int rid_alloc () ; 
 struct resource* rid_lookup (int) ; 
 int snprintf (char*,int,char*,char const*,char const*) ; 

int
bs_map(const char *dev, const char *res)
{
	char path[PATH_MAX];
	struct proto_ioc_region region;
	struct resource *r;
	int len, rid;

	len = snprintf(path, PATH_MAX, "/dev/proto/%s/%s", dev, res);
	if (len >= PATH_MAX) {
		errno = EINVAL;
		return (-1);
	}
	rid = rid_alloc();
	if (rid == -1)
		return (-1);
	r = rid_lookup(rid);
	if (r == NULL)
		return (-1);
	r->fd = open(path, O_RDWR);
	if (r->fd == -1)
		return (-1);
	r->rid = -1;
	if (ioctl(r->fd, PROTO_IOC_REGION, &region) == -1) {
		close(r->fd);
		r->fd = -1;
		return (-1);
	}
	r->addr = region.address;
	r->size = region.size;
	r->ofs = 0;
	r->ptr = mmap(NULL, r->size, PROT_READ | PROT_WRITE,
	    MAP_NOCORE | MAP_SHARED, r->fd, r->ofs);
	return (rid);
}