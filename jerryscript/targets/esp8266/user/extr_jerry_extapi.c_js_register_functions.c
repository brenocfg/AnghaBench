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
 int /*<<< orphan*/  REGISTER_HANDLER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert ; 
 int /*<<< orphan*/  gpio_dir ; 
 int /*<<< orphan*/  gpio_get ; 
 int /*<<< orphan*/  gpio_set ; 
 int /*<<< orphan*/  print ; 

void js_register_functions (void)
{
  REGISTER_HANDLER(assert);
  REGISTER_HANDLER(print);
  REGISTER_HANDLER(gpio_dir);
  REGISTER_HANDLER(gpio_set);
  REGISTER_HANDLER(gpio_get);
}