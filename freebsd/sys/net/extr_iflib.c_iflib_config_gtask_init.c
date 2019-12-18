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
struct grouptask {int dummy; } ;
typedef  int /*<<< orphan*/  gtask_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  GROUPTASK_INIT (struct grouptask*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  qgroup_if_config_tqg ; 
 int /*<<< orphan*/  taskqgroup_attach (int /*<<< orphan*/ ,struct grouptask*,struct grouptask*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

void
iflib_config_gtask_init(void *ctx, struct grouptask *gtask, gtask_fn_t *fn,
	const char *name)
{

	GROUPTASK_INIT(gtask, 0, fn, ctx);
	taskqgroup_attach(qgroup_if_config_tqg, gtask, gtask, NULL, NULL,
	    name);
}