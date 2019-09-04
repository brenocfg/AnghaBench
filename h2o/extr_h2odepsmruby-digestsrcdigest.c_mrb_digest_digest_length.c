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
 int /*<<< orphan*/  basecheck (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mrb_md**) ; 
 int /*<<< orphan*/  lib_md_digest_length (struct mrb_md*) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_digest_digest_length(mrb_state *mrb, mrb_value self)
{
  struct mrb_md *md;

  basecheck(mrb, self, &md);
  return mrb_fixnum_value(lib_md_digest_length(md));
}