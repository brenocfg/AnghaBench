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
 void* idr_find_locked (struct idr*,int) ; 
 int idr_max (struct idr*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void *
idr_get_next(struct idr *idr, int *nextidp)
{
	void *res = NULL;
	int id = *nextidp;

	mtx_lock(&idr->lock);
	for (; id <= idr_max(idr); id++) {
		res = idr_find_locked(idr, id);
		if (res == NULL)
			continue;
		*nextidp = id;
		break;
	}
	mtx_unlock(&idr->lock);
	return (res);
}