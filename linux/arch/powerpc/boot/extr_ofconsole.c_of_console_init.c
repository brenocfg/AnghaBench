#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  write; int /*<<< orphan*/  open; } ;

/* Variables and functions */
 TYPE_1__ console_ops ; 
 int /*<<< orphan*/  of_console_open ; 
 int /*<<< orphan*/  of_console_write ; 

void of_console_init(void)
{
	console_ops.open = of_console_open;
	console_ops.write = of_console_write;
}