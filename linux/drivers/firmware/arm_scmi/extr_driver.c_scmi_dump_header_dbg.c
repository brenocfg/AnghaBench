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
struct scmi_msg_hdr {int /*<<< orphan*/  protocol_id; int /*<<< orphan*/  seq; int /*<<< orphan*/  id; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void scmi_dump_header_dbg(struct device *dev,
					struct scmi_msg_hdr *hdr)
{
	dev_dbg(dev, "Message ID: %x Sequence ID: %x Protocol: %x\n",
		hdr->id, hdr->seq, hdr->protocol_id);
}