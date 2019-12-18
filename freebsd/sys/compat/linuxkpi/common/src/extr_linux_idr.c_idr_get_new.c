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
struct idr {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int idr_get_new_locked (struct idr*,void*,int*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
idr_get_new(struct idr *idr, void *ptr, int *idp)
{
	int retval;

	mtx_lock(&idr->lock);
	retval = idr_get_new_locked(idr, ptr, idp);
	mtx_unlock(&idr->lock);
	return (retval);
}