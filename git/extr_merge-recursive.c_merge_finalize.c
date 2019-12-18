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
struct merge_options {int buffer_output; TYPE_1__* priv; int /*<<< orphan*/  obuf; } ;
struct TYPE_2__ {int /*<<< orphan*/  needed_rename_limit; int /*<<< orphan*/  call_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (TYPE_1__*) ; 
 int /*<<< orphan*/  diff_warn_rename_limit (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_output (struct merge_options*) ; 
 scalar_t__ show (struct merge_options*,int) ; 
 int /*<<< orphan*/  strbuf_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void merge_finalize(struct merge_options *opt)
{
	flush_output(opt);
	if (!opt->priv->call_depth && opt->buffer_output < 2)
		strbuf_release(&opt->obuf);
	if (show(opt, 2))
		diff_warn_rename_limit("merge.renamelimit",
				       opt->priv->needed_rename_limit, 0);
	FREE_AND_NULL(opt->priv);
}