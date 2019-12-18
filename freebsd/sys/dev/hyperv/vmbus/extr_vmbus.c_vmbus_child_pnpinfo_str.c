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
struct vmbus_channel {int /*<<< orphan*/  ch_guid_inst; int /*<<< orphan*/  ch_guid_type; } ;
typedef  int /*<<< orphan*/  guidbuf ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int HYPERV_GUID_STRLEN ; 
 int /*<<< orphan*/  hyperv_guid2str (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 
 struct vmbus_channel* vmbus_get_channel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vmbus_child_pnpinfo_str(device_t dev, device_t child, char *buf, size_t buflen)
{
	const struct vmbus_channel *chan;
	char guidbuf[HYPERV_GUID_STRLEN];

	chan = vmbus_get_channel(child);
	if (chan == NULL) {
		/* Event timer device, which does not belong to a channel */
		return (0);
	}

	strlcat(buf, "classid=", buflen);
	hyperv_guid2str(&chan->ch_guid_type, guidbuf, sizeof(guidbuf));
	strlcat(buf, guidbuf, buflen);

	strlcat(buf, " deviceid=", buflen);
	hyperv_guid2str(&chan->ch_guid_inst, guidbuf, sizeof(guidbuf));
	strlcat(buf, guidbuf, buflen);

	return (0);
}