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
struct TYPE_2__ {int /*<<< orphan*/  pool; } ;
struct ib_conn {int /*<<< orphan*/  lock; TYPE_1__ fastreg; } ;
struct fast_reg_descriptor {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
iser_reg_desc_put(struct ib_conn *ib_conn,
		  struct fast_reg_descriptor *desc)
{
	mtx_lock(&ib_conn->lock);
	list_add(&desc->list, &ib_conn->fastreg.pool);
	mtx_unlock(&ib_conn->lock);
}