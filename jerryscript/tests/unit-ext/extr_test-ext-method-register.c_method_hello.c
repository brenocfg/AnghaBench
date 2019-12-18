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
 int /*<<< orphan*/  jerry_create_number (int /*<<< orphan*/  const) ; 

__attribute__((used)) static jerry_value_t
method_hello (const jerry_value_t jfunc,  /**< function object */
              const jerry_value_t jthis,  /**< function this */
              const jerry_value_t jargv[], /**< arguments */
              const jerry_length_t jargc) /**< number of arguments */
{
  (void) jfunc;
  (void) jthis;
  (void) jargv;
  return jerry_create_number (jargc);
}