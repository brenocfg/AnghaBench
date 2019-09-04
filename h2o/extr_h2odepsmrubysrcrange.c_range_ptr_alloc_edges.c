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
struct RRange {int /*<<< orphan*/ * edges; } ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_range_edges ;

/* Variables and functions */
 scalar_t__ mrb_malloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
range_ptr_alloc_edges(mrb_state *mrb, struct RRange *r)
{
#ifndef MRB_RANGE_EMBED
  r->edges = (mrb_range_edges *)mrb_malloc(mrb, sizeof(mrb_range_edges));
#endif
}