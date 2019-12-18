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
struct cma_id_private {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  fastlock_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fastlock_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idm_lock ; 
 int /*<<< orphan*/  idm_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct cma_id_private*) ; 
 int /*<<< orphan*/  ucma_idm ; 

__attribute__((used)) static void ucma_insert_id(struct cma_id_private *id_priv)
{
	fastlock_acquire(&idm_lock);
	idm_set(&ucma_idm, id_priv->handle, id_priv);
	fastlock_release(&idm_lock);
}