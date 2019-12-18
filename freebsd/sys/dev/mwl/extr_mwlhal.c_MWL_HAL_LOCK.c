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
struct mwl_hal_priv {int /*<<< orphan*/  mh_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline void
MWL_HAL_LOCK(struct mwl_hal_priv *mh)
{
	mtx_lock(&mh->mh_mtx);
}