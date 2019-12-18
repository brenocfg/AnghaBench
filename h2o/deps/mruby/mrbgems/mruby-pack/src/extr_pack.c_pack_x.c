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
typedef  long mrb_int ;

/* Variables and functions */
 char* RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str_len_ensure (int /*<<< orphan*/ *,int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static int
pack_x(mrb_state *mrb, mrb_value src, mrb_value dst, mrb_int didx, long count, unsigned int flags)
{
  long i;

  if (count < 0) return 0;
  dst = str_len_ensure(mrb, dst, didx + count);
  for (i = 0; i < count; i++) {
    RSTRING_PTR(dst)[didx + i] = '\0';
  }
  return count;
}