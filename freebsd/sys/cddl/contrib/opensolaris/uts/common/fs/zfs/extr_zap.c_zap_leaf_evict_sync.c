#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  l_rwlock; } ;
typedef  TYPE_1__ zap_leaf_t ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  rw_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
zap_leaf_evict_sync(void *dbu)
{
	zap_leaf_t *l = dbu;

	rw_destroy(&l->l_rwlock);
	kmem_free(l, sizeof (zap_leaf_t));
}