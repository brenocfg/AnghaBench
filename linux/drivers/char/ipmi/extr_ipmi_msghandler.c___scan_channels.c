#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ipmi_smi {unsigned int curr_working_cset; int channels_ready; TYPE_2__* wchannels; TYPE_2__* channel_list; int /*<<< orphan*/ * null_user_handler; int /*<<< orphan*/  waitq; int /*<<< orphan*/  si_dev; scalar_t__ curr_channel; } ;
struct ipmi_device_id {int dummy; } ;
struct ipmi_channel_set {int dummy; } ;
struct TYPE_4__ {TYPE_1__* c; } ;
struct TYPE_3__ {int /*<<< orphan*/  protocol; int /*<<< orphan*/  medium; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IPMI_CHANNEL_MEDIUM_IPMB ; 
 int /*<<< orphan*/  IPMI_CHANNEL_PROTOCOL_IPMB ; 
 int /*<<< orphan*/ * channel_handler ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int ipmi_version_major (struct ipmi_device_id*) ; 
 int ipmi_version_minor (struct ipmi_device_id*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int send_channel_info_cmd (struct ipmi_smi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __scan_channels(struct ipmi_smi *intf, struct ipmi_device_id *id)
{
	int rv;

	if (ipmi_version_major(id) > 1
			|| (ipmi_version_major(id) == 1
			    && ipmi_version_minor(id) >= 5)) {
		unsigned int set;

		/*
		 * Start scanning the channels to see what is
		 * available.
		 */
		set = !intf->curr_working_cset;
		intf->curr_working_cset = set;
		memset(&intf->wchannels[set], 0,
		       sizeof(struct ipmi_channel_set));

		intf->null_user_handler = channel_handler;
		intf->curr_channel = 0;
		rv = send_channel_info_cmd(intf, 0);
		if (rv) {
			dev_warn(intf->si_dev,
				 "Error sending channel information for channel 0, %d\n",
				 rv);
			return -EIO;
		}

		/* Wait for the channel info to be read. */
		wait_event(intf->waitq, intf->channels_ready);
		intf->null_user_handler = NULL;
	} else {
		unsigned int set = intf->curr_working_cset;

		/* Assume a single IPMB channel at zero. */
		intf->wchannels[set].c[0].medium = IPMI_CHANNEL_MEDIUM_IPMB;
		intf->wchannels[set].c[0].protocol = IPMI_CHANNEL_PROTOCOL_IPMB;
		intf->channel_list = intf->wchannels + set;
		intf->channels_ready = true;
	}

	return 0;
}