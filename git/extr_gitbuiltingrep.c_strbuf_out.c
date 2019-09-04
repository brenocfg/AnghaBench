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
struct work_item {int /*<<< orphan*/  out; } ;
struct grep_opt {struct work_item* output_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_add (int /*<<< orphan*/ *,void const*,size_t) ; 

__attribute__((used)) static void strbuf_out(struct grep_opt *opt, const void *buf, size_t size)
{
	struct work_item *w = opt->output_priv;
	strbuf_add(&w->out, buf, size);
}