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
struct bstp_state {int /*<<< orphan*/  bs_bstpcallout; int /*<<< orphan*/  bs_bplist; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTP_LOCK_DESTROY (struct bstp_state*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct bstp_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bs_list ; 
 int /*<<< orphan*/  bstp_list_mtx ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
bstp_detach(struct bstp_state *bs)
{
	KASSERT(LIST_EMPTY(&bs->bs_bplist), ("bstp still active"));

	mtx_lock(&bstp_list_mtx);
	LIST_REMOVE(bs, bs_list);
	mtx_unlock(&bstp_list_mtx);
	callout_drain(&bs->bs_bstpcallout);
	BSTP_LOCK_DESTROY(bs);
}