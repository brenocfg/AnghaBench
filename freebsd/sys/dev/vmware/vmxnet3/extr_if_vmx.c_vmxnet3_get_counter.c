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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  ift_counter ;
typedef  int /*<<< orphan*/  if_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTERS ; 
 int /*<<< orphan*/  if_get_counter_default (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_get_ifp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
vmxnet3_get_counter(if_ctx_t ctx, ift_counter cnt)
{
	if_t ifp = iflib_get_ifp(ctx);

	if (cnt < IFCOUNTERS)
		return if_get_counter_default(ifp, cnt);

	return (0);
}