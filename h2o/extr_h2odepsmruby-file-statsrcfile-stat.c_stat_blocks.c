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
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_nil_value () ; 

__attribute__((used)) static mrb_value
stat_blocks(mrb_state *mrb, mrb_value self)
{
#ifdef HAVE_STRUCT_STAT_ST_BLOCKS
  return mrb_ll2num(mrb, get_stat(mrb, self)->st_blocks);
#else
  return mrb_nil_value();
#endif
}