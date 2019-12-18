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
struct vmbus_channel {int /*<<< orphan*/  ch_guid_type; } ;
struct hyperv_guid {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,struct hyperv_guid const*,int) ; 
 struct vmbus_channel* vmbus_get_channel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vmbus_probe_guid_method(device_t bus, device_t dev,
    const struct hyperv_guid *guid)
{
	const struct vmbus_channel *chan = vmbus_get_channel(dev);

	if (memcmp(&chan->ch_guid_type, guid, sizeof(struct hyperv_guid)) == 0)
		return 0;
	return ENXIO;
}