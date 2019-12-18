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
typedef  int /*<<< orphan*/  heap_context ;
typedef  int /*<<< orphan*/  evContext_p ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  due_sooner ; 
 int /*<<< orphan*/  heap_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_index ; 

heap_context
evCreateTimers(const evContext_p *ctx) {

	UNUSED(ctx);

	return (heap_new(due_sooner, set_index, 2048));
}