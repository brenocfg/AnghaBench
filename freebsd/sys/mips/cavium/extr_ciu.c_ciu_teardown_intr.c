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
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int intr_event_remove_handler (void*) ; 

__attribute__((used)) static int
ciu_teardown_intr(device_t bus, device_t child, struct resource *res,
		  void *cookie)
{
	int error;

	error = intr_event_remove_handler(cookie);
	if (error != 0)
		return (error);

	return (0);
}