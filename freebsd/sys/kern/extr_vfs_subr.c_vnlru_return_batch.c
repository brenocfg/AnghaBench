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
struct mount {int /*<<< orphan*/  mnt_listmtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnlru_return_batch_locked (struct mount*) ; 

__attribute__((used)) static void
vnlru_return_batch(struct mount *mp)
{

	mtx_lock(&mp->mnt_listmtx);
	vnlru_return_batch_locked(mp);
	mtx_unlock(&mp->mnt_listmtx);
}