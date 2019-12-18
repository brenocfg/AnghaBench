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
struct fha_hash_entry {int num_exclusive; int num_rw; int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int LK_EXCLUSIVE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fha_hash_entry_add_op(struct fha_hash_entry *fhe, int locktype, int count)
{

	mtx_assert(fhe->mtx, MA_OWNED);
	if (LK_EXCLUSIVE == locktype)
		fhe->num_exclusive += count;
	else
		fhe->num_rw += count;
}