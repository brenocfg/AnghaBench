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
 int /*<<< orphan*/  MRB_FROZEN_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MRB_SET_FROZEN_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_string_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline mrb_value
ht_key(mrb_state *mrb, mrb_value key)
{
  if (mrb_string_p(key) && !MRB_FROZEN_P(mrb_str_ptr(key))) {
    key = mrb_str_dup(mrb, key);
    MRB_SET_FROZEN_FLAG(mrb_str_ptr(key));
  }
  return key;
}