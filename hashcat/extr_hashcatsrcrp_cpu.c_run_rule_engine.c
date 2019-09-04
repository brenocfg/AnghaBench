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

/* Variables and functions */
 char const RULE_OP_MANGLE_NOOP ; 

int run_rule_engine (const int rule_len, const char *rule_buf)
{
  if (rule_len == 0) return 0;

  if (rule_len == 1)
    if (rule_buf[0] == RULE_OP_MANGLE_NOOP) return 0;

  return 1;
}