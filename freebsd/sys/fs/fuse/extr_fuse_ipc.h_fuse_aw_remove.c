#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * tqe_prev; int /*<<< orphan*/ * tqe_next; } ;
struct fuse_ticket {TYPE_2__ tk_aw_link; TYPE_1__* tk_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  aw_head; int /*<<< orphan*/  aw_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct fuse_ticket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tk_aw_link ; 

__attribute__((used)) static inline void
fuse_aw_remove(struct fuse_ticket *ftick)
{
	mtx_assert(&ftick->tk_data->aw_mtx, MA_OWNED);
	TAILQ_REMOVE(&ftick->tk_data->aw_head, ftick, tk_aw_link);
#ifdef INVARIANTS
	ftick->tk_aw_link.tqe_next = NULL;
	ftick->tk_aw_link.tqe_prev = NULL;
#endif
}