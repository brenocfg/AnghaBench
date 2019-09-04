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
typedef  int /*<<< orphan*/  mrb_int ;

/* Variables and functions */
 scalar_t__ DATA_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lib_md_update (int /*<<< orphan*/ *,struct mrb_md*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 

__attribute__((used)) static mrb_value
mrb_digest_update(mrb_state *mrb, mrb_value self)
{
  struct mrb_md *md;
  mrb_int len;
  char *str;

  md = (struct mrb_md *)DATA_PTR(self);
  if (!md) return mrb_nil_value();
  mrb_get_args(mrb, "s", &str, &len);
  lib_md_update(mrb, md, (unsigned char *)str, len);
  return self;
}