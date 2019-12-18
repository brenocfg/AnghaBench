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
 int /*<<< orphan*/  find_regno (char const*) ; 
 int /*<<< orphan*/  supply_register (int /*<<< orphan*/ ,void const*) ; 

void
supply_register_by_name (const char *name, const void *buf)
{
  supply_register (find_regno (name), buf);
}