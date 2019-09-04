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
typedef  int mrb_int ;

/* Variables and functions */
 int CHAR_BIT ; 
 int /*<<< orphan*/  E_RANGE_ERROR ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_new (int /*<<< orphan*/ *,char*,int) ; 
 int to_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_int_chr(mrb_state *mrb, mrb_value x)
{
  mrb_int chr;
  char c;

  chr = to_int(mrb, x);
  if (chr >= (1 << CHAR_BIT)) {
    mrb_raisef(mrb, E_RANGE_ERROR, "%S out of char range", x);
  }
  c = (char)chr;

  return mrb_str_new(mrb, &c, 1);
}