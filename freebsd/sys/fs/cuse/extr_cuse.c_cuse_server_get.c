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
struct cuse_server {scalar_t__ is_closing; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cuse_lock () ; 
 int /*<<< orphan*/  cuse_unlock () ; 
 int devfs_get_cdevpriv (void**) ; 

__attribute__((used)) static int
cuse_server_get(struct cuse_server **ppcs)
{
	struct cuse_server *pcs;
	int error;

	error = devfs_get_cdevpriv((void **)&pcs);
	if (error != 0) {
		*ppcs = NULL;
		return (error);
	}
	/* check if closing */
	cuse_lock();
	if (pcs->is_closing) {
		cuse_unlock();
		*ppcs = NULL;
		return (EINVAL);
	}
	cuse_unlock();
	*ppcs = pcs;
	return (0);
}