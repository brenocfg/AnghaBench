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
struct umtx_shm_reg {int dummy; } ;
struct umtx_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 struct umtx_shm_reg* umtx_shm_find_reg_locked (struct umtx_key const*) ; 
 int /*<<< orphan*/  umtx_shm_lock ; 

__attribute__((used)) static struct umtx_shm_reg *
umtx_shm_find_reg(const struct umtx_key *key)
{
	struct umtx_shm_reg *reg;

	mtx_lock(&umtx_shm_lock);
	reg = umtx_shm_find_reg_locked(key);
	mtx_unlock(&umtx_shm_lock);
	return (reg);
}