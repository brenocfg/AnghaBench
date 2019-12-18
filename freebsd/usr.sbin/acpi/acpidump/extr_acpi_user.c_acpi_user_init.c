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
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int acpi_mem_fd ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  maplist ; 
 int open (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
acpi_user_init(void)
{

	if (acpi_mem_fd == -1) {
		acpi_mem_fd = open("/dev/mem", O_RDONLY);
		if (acpi_mem_fd == -1)
			err(1, "opening /dev/mem");
		LIST_INIT(&maplist);
	}
}