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
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  int /*<<< orphan*/  jerry_length_t ;

/* Variables and functions */
 int /*<<< orphan*/  jerry_create_undefined () ; 

__attribute__((used)) static jerry_value_t
my_constructor (const jerry_value_t func_val, /**< function */
                const jerry_value_t this_val, /**< this */
                const jerry_value_t argv[], /**< arguments */
                const jerry_length_t argc) /**< number of arguments */
{
  (void) func_val;
  (void) this_val;
  (void) argv;
  (void) argc;
  return jerry_create_undefined ();
}