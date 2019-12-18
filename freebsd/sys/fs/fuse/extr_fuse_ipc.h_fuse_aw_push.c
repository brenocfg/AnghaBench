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
struct fuse_ticket {TYPE_1__* tk_data; int /*<<< orphan*/  tk_refcount; } ;
struct TYPE_2__ {int /*<<< orphan*/  aw_head; int /*<<< orphan*/  aw_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct fuse_ticket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tk_aw_link ; 

__attribute__((used)) static inline void
fuse_aw_push(struct fuse_ticket *ftick)
{
	mtx_assert(&ftick->tk_data->aw_mtx, MA_OWNED);
	refcount_acquire(&ftick->tk_refcount);
	TAILQ_INSERT_TAIL(&ftick->tk_data->aw_head, ftick, tk_aw_link);
}