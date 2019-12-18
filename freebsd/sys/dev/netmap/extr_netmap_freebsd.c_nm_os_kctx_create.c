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
struct nm_kctx_cfg {int /*<<< orphan*/  attach_user; int /*<<< orphan*/  type; int /*<<< orphan*/  worker_private; int /*<<< orphan*/  worker_fn; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; int /*<<< orphan*/  worker_private; int /*<<< orphan*/  worker_fn; } ;
struct nm_kctx {int affinity; int /*<<< orphan*/  attach_user; TYPE_1__ worker_ctx; int /*<<< orphan*/  worker_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 struct nm_kctx* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct nm_kctx *
nm_os_kctx_create(struct nm_kctx_cfg *cfg, void *opaque)
{
	struct nm_kctx *nmk = NULL;

	nmk = malloc(sizeof(*nmk),  M_DEVBUF, M_NOWAIT | M_ZERO);
	if (!nmk)
		return NULL;

	mtx_init(&nmk->worker_lock, "nm_kthread lock", NULL, MTX_DEF);
	nmk->worker_ctx.worker_fn = cfg->worker_fn;
	nmk->worker_ctx.worker_private = cfg->worker_private;
	nmk->worker_ctx.type = cfg->type;
	nmk->affinity = -1;

	/* attach kthread to user process (ptnetmap) */
	nmk->attach_user = cfg->attach_user;

	return nmk;
}