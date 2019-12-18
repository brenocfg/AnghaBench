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

/* Variables and functions */
 int /*<<< orphan*/  M_SIFTR ; 
 int /*<<< orphan*/  SIFTR_DISABLE ; 
 int /*<<< orphan*/  counter_hash ; 
 int /*<<< orphan*/  hashdestroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  siftr_hashmask ; 
 int /*<<< orphan*/  siftr_manage_ops (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siftr_pkt_mgr_mtx ; 
 int /*<<< orphan*/  siftr_pkt_queue_mtx ; 

__attribute__((used)) static int
deinit_siftr(void)
{
	/* Cleanup. */
	siftr_manage_ops(SIFTR_DISABLE);
	hashdestroy(counter_hash, M_SIFTR, siftr_hashmask);
	mtx_destroy(&siftr_pkt_queue_mtx);
	mtx_destroy(&siftr_pkt_mgr_mtx);

	return (0);
}