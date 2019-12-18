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
struct cryptop_data {int done; TYPE_1__* cse; } ;
struct cryptop {struct cryptop_data* crp_opaque; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct cryptop_data*) ; 

__attribute__((used)) static int
cryptodev_cb(struct cryptop *crp)
{
	struct cryptop_data *cod = crp->crp_opaque;

	/*
	 * Lock to ensure the wakeup() is not missed by the loops
	 * waiting on cod->done in cryptodev_op() and
	 * cryptodev_aead().
	 */
	mtx_lock(&cod->cse->lock);
	cod->done = true;
	mtx_unlock(&cod->cse->lock);
	wakeup(cod);
	return (0);
}