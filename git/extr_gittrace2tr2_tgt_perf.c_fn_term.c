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

/* Variables and functions */
 int /*<<< orphan*/  dots ; 
 int /*<<< orphan*/  strbuf_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tr2_dst_trace_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tr2dst_perf ; 

__attribute__((used)) static void fn_term(void)
{
	tr2_dst_trace_disable(&tr2dst_perf);

	strbuf_release(&dots);
}