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
struct tr2_dst {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tr2_dst_get_trace_fd (struct tr2_dst*) ; 

int tr2_dst_trace_want(struct tr2_dst *dst)
{
	return !!tr2_dst_get_trace_fd(dst);
}