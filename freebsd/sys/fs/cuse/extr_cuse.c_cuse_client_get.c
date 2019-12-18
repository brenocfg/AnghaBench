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
struct cuse_client {TYPE_1__* server; } ;
struct TYPE_2__ {scalar_t__ is_closing; } ;

/* Variables and functions */
 scalar_t__ CUSE_CLIENT_CLOSING (struct cuse_client*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  cuse_lock () ; 
 int /*<<< orphan*/  cuse_unlock () ; 
 int devfs_get_cdevpriv (void**) ; 

__attribute__((used)) static int
cuse_client_get(struct cuse_client **ppcc)
{
	struct cuse_client *pcc;
	int error;

	/* try to get private data */
	error = devfs_get_cdevpriv((void **)&pcc);
	if (error != 0) {
		*ppcc = NULL;
		return (error);
	}
	/* check if closing */
	cuse_lock();
	if (CUSE_CLIENT_CLOSING(pcc) || pcc->server->is_closing) {
		cuse_unlock();
		*ppcc = NULL;
		return (EINVAL);
	}
	cuse_unlock();
	*ppcc = pcc;
	return (0);
}