#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int dtype; } ;
typedef  TYPE_1__ token ;

/* Variables and functions */
 int /*<<< orphan*/  F (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char* token_buff ; 
 int /*<<< orphan*/  v_cstring ; 
 int /*<<< orphan*/  v_double ; 
 int /*<<< orphan*/  v_int ; 
 int /*<<< orphan*/  v_long ; 
 int /*<<< orphan*/  v_string ; 

char *token_val_to_str (token *tok) {
  char *s = token_buff;

  switch (tok->dtype) {
    F("%d", v_int);
    F("%lf", v_double);
    F("%lld", v_long);
    F("%s", v_string);
    F("%s", v_cstring);
    default:
      assert (0);
  }
#undef F
  return token_buff;
}