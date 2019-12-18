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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct xive_q {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __xive_native_disable_queue (int /*<<< orphan*/ ,struct xive_q*,int /*<<< orphan*/ ) ; 

void xive_native_disable_queue(u32 vp_id, struct xive_q *q, u8 prio)
{
	__xive_native_disable_queue(vp_id, q, prio);
}