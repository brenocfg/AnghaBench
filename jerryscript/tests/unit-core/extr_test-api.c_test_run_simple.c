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
typedef  int /*<<< orphan*/  jerry_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_INIT_EMPTY ; 
 int jerry_run_simple (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static bool
test_run_simple (const char *script_p) /**< source code to run */
{
  size_t script_size = strlen (script_p);

  return jerry_run_simple ((const jerry_char_t *) script_p, script_size, JERRY_INIT_EMPTY);
}