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
struct resource {int rid; scalar_t__ ptr; int fd; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 scalar_t__ MAP_FAILED ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  munmap (scalar_t__,int /*<<< orphan*/ ) ; 
 struct resource* rid_lookup (int) ; 

int
bs_unmap(int rid)
{
	struct resource *r;

	r = rid_lookup(rid);
	if (r == NULL)
		return (0);
	if (r->rid == -1) {
		if (r->ptr != MAP_FAILED)
			munmap(r->ptr, r->size);
		close(r->fd);
	}
	r->fd = -1;
	return (1);
}