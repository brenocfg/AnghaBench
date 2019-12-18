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
 int /*<<< orphan*/  ACPIDEV ; 
 int /*<<< orphan*/  EX_OSFILE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_RDWR ; 
 int acpifd ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
acpi_init(void)
{
	acpifd = open(ACPIDEV, O_RDWR);
	if (acpifd == -1)
		acpifd = open(ACPIDEV, O_RDONLY);
	if (acpifd == -1)
		err(EX_OSFILE, ACPIDEV);
}