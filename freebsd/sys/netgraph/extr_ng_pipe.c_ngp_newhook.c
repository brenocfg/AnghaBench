#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int qin_size_limit; int fifo; int droptail; } ;
struct hookinfo {int /*<<< orphan*/  qout_head; int /*<<< orphan*/  fifo_head; TYPE_1__ cfg; } ;
typedef  TYPE_2__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  void* hook_p ;
struct TYPE_8__ {void* hook; } ;
struct TYPE_7__ {TYPE_3__ lower; TYPE_3__ upper; } ;

/* Variables and functions */
 int EINVAL ; 
 struct hookinfo* NG_HOOK_PRIVATE (void*) ; 
 int /*<<< orphan*/  NG_HOOK_SET_PRIVATE (void*,TYPE_3__*) ; 
 TYPE_2__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_PIPE_HOOK_LOWER ; 
 int /*<<< orphan*/  NG_PIPE_HOOK_UPPER ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (TYPE_3__*,int) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ngp_newhook(node_p node, hook_p hook, const char *name)
{
	const priv_p priv = NG_NODE_PRIVATE(node);
	struct hookinfo *hinfo;

	if (strcmp(name, NG_PIPE_HOOK_UPPER) == 0) {
		bzero(&priv->upper, sizeof(priv->upper));
		priv->upper.hook = hook;
		NG_HOOK_SET_PRIVATE(hook, &priv->upper);
	} else if (strcmp(name, NG_PIPE_HOOK_LOWER) == 0) {
		bzero(&priv->lower, sizeof(priv->lower));
		priv->lower.hook = hook;
		NG_HOOK_SET_PRIVATE(hook, &priv->lower);
	} else
		return (EINVAL);

	/* Load non-zero initial cfg values */
	hinfo = NG_HOOK_PRIVATE(hook);
	hinfo->cfg.qin_size_limit = 50;
	hinfo->cfg.fifo = 1;
	hinfo->cfg.droptail = 1;
	TAILQ_INIT(&hinfo->fifo_head);
	TAILQ_INIT(&hinfo->qout_head);
	return (0);
}