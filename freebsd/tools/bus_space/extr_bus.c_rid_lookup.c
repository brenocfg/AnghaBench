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
struct resource {int fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  errno ; 
 int nrids ; 
 struct resource* ridtbl ; 

__attribute__((used)) static struct resource *
rid_lookup(int rid)
{
	struct resource *r;

	if (rid < 0 || rid >= nrids) {
		errno = EINVAL;
		return (NULL);
	}
	r = ridtbl + rid;
	if (r->fd == -1) {
		errno = ENXIO;
		return (NULL);
	}
	return (r);
}