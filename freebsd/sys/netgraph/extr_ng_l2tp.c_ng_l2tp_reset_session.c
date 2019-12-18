#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ng_l2tp_session_stats {int dummy; } ;
typedef  TYPE_2__* hookpriv_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_4__ {scalar_t__ enable_dseq; scalar_t__ control_dseq; } ;
struct TYPE_5__ {scalar_t__ ns; scalar_t__ nr; int /*<<< orphan*/  stats; TYPE_1__ conf; } ;

/* Variables and functions */
 TYPE_2__* NG_HOOK_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ng_l2tp_reset_session(hook_p hook, void *arg)
{
	const hookpriv_p hpriv = NG_HOOK_PRIVATE(hook);

	if (hpriv != NULL) {
		hpriv->conf.control_dseq = 0;
		hpriv->conf.enable_dseq = 0;
		bzero(&hpriv->stats, sizeof(struct ng_l2tp_session_stats));
		hpriv->nr = 0;
		hpriv->ns = 0;
	}
	return (-1);
}