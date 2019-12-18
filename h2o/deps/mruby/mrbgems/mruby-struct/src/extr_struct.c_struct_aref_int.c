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
typedef  size_t mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  E_INDEX_ERROR ; 
 size_t RSTRUCT_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RSTRUCT_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (size_t) ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
struct_aref_int(mrb_state *mrb, mrb_value s, mrb_int i)
{
  if (i < 0) i = RSTRUCT_LEN(s) + i;
  if (i < 0)
      mrb_raisef(mrb, E_INDEX_ERROR,
                 "offset %S too small for struct(size:%S)",
                 mrb_fixnum_value(i), mrb_fixnum_value(RSTRUCT_LEN(s)));
  if (RSTRUCT_LEN(s) <= i)
    mrb_raisef(mrb, E_INDEX_ERROR,
               "offset %S too large for struct(size:%S)",
               mrb_fixnum_value(i), mrb_fixnum_value(RSTRUCT_LEN(s)));
  return RSTRUCT_PTR(s)[i];
}