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
struct seq_file {int dummy; } ;
struct blk_mq_hw_ctx {size_t type; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ HCTX_MAX_TYPES ; 
 int /*<<< orphan*/ * hctx_types ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hctx_type_show(void *data, struct seq_file *m)
{
	struct blk_mq_hw_ctx *hctx = data;

	BUILD_BUG_ON(ARRAY_SIZE(hctx_types) != HCTX_MAX_TYPES);
	seq_printf(m, "%s\n", hctx_types[hctx->type]);
	return 0;
}