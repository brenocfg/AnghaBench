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
typedef  int /*<<< orphan*/  jerry_context_t ;

/* Variables and functions */
 int /*<<< orphan*/ * current_context_p ; 

void
jerry_port_default_set_current_context (jerry_context_t *context_p) /**< points to the created context */
{
  current_context_p = context_p;
}