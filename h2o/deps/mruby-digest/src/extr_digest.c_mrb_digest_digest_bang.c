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
struct mrb_md {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 scalar_t__ DATA_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lib_md_digest_bang (int /*<<< orphan*/ *,struct mrb_md*) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 

__attribute__((used)) static mrb_value
mrb_digest_digest_bang(mrb_state *mrb, mrb_value self)
{
  struct mrb_md *md;

  md = (struct mrb_md *)DATA_PTR(self);
  if (!md) return mrb_nil_value();
  return lib_md_digest_bang(mrb, md);
}