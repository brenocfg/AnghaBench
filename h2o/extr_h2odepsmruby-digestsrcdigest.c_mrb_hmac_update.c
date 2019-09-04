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
struct mrb_hmac {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_int ;

/* Variables and functions */
 scalar_t__ DATA_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lib_hmac_update (int /*<<< orphan*/ *,struct mrb_hmac*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 

__attribute__((used)) static mrb_value
mrb_hmac_update(mrb_state *mrb, mrb_value self)
{
  struct mrb_hmac *hmac;
  mrb_int len;
  char *str;

  hmac = (struct mrb_hmac *)DATA_PTR(self);
  if (!hmac) return mrb_nil_value();
  mrb_get_args(mrb, "s", &str, &len);
  lib_hmac_update(mrb, hmac, (unsigned char *)str, len);
  return self;
}