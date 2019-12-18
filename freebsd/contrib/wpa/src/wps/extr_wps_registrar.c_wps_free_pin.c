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
struct wps_uuid_pin {int /*<<< orphan*/  pin_len; int /*<<< orphan*/  pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  bin_clear_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct wps_uuid_pin*) ; 

__attribute__((used)) static void wps_free_pin(struct wps_uuid_pin *pin)
{
	bin_clear_free(pin->pin, pin->pin_len);
	os_free(pin);
}