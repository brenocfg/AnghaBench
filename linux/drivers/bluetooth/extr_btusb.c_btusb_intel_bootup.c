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
struct intel_bootup {int dummy; } ;
struct btusb_data {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTUSB_BOOTING ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btusb_intel_bootup(struct btusb_data *data, const void *ptr,
			       unsigned int len)
{
	const struct intel_bootup *evt = ptr;

	if (len != sizeof(*evt))
		return;

	if (test_and_clear_bit(BTUSB_BOOTING, &data->flags))
		wake_up_bit(&data->flags, BTUSB_BOOTING);
}