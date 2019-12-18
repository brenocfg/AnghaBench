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
typedef  int /*<<< orphan*/  jv ;
typedef  int /*<<< orphan*/  block ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_list_funcs (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_const (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_function (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_noop () ; 
 int /*<<< orphan*/  jv_array_append (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string (char*) ; 

__attribute__((used)) static block gen_builtin_list(block builtins) {
  jv list = jv_array_append(block_list_funcs(builtins, 1), jv_string("builtins/0"));
  return BLOCK(builtins, gen_function("builtins", gen_noop(), gen_const(list)));
}