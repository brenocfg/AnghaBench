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
struct nbd_device {int /*<<< orphan*/  index; int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nbd_dev_remove (struct nbd_device*) ; 
 int /*<<< orphan*/  nbd_index_idr ; 
 int /*<<< orphan*/  nbd_index_mutex ; 
 scalar_t__ refcount_dec_and_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nbd_put(struct nbd_device *nbd)
{
	if (refcount_dec_and_mutex_lock(&nbd->refs,
					&nbd_index_mutex)) {
		idr_remove(&nbd_index_idr, nbd->index);
		nbd_dev_remove(nbd);
		mutex_unlock(&nbd_index_mutex);
	}
}