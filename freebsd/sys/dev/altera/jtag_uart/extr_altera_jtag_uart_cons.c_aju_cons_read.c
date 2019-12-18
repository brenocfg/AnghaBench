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
 int /*<<< orphan*/  AJU_CONSOLE_LOCK_ASSERT () ; 
 char aju_cons_buffer_data ; 
 scalar_t__ aju_cons_buffer_valid ; 
 int /*<<< orphan*/  aju_cons_readable () ; 

__attribute__((used)) static char
aju_cons_read(void)
{

	AJU_CONSOLE_LOCK_ASSERT();

	while (!aju_cons_readable());
	aju_cons_buffer_valid = 0;
	return (aju_cons_buffer_data);
}