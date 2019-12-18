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
struct TYPE_2__ {int /*<<< orphan*/ * stqe_next; } ;
struct fuse_ticket {TYPE_1__ tk_ms_link; } ;
struct fuse_data {scalar_t__ ms_count; int /*<<< orphan*/  ms_head; int /*<<< orphan*/  ms_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int) ; 
 struct fuse_ticket* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tk_ms_link ; 

__attribute__((used)) static inline struct fuse_ticket *
fuse_ms_pop(struct fuse_data *data)
{
	struct fuse_ticket *ftick = NULL;

	mtx_assert(&data->ms_mtx, MA_OWNED);

	if ((ftick = STAILQ_FIRST(&data->ms_head))) {
		STAILQ_REMOVE_HEAD(&data->ms_head, tk_ms_link);
		data->ms_count--;
#ifdef INVARIANTS
		MPASS(data->ms_count >= 0);
		ftick->tk_ms_link.stqe_next = NULL;
#endif
	}

	return (ftick);
}