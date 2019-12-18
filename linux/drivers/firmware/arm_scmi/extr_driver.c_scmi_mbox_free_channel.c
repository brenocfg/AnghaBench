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
struct scmi_chan_info {int /*<<< orphan*/ * chan; } ;
struct idr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_remove (struct idr*,int) ; 
 int /*<<< orphan*/  mbox_free_channel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int scmi_mbox_free_channel(int id, void *p, void *data)
{
	struct scmi_chan_info *cinfo = p;
	struct idr *idr = data;

	if (!IS_ERR_OR_NULL(cinfo->chan)) {
		mbox_free_channel(cinfo->chan);
		cinfo->chan = NULL;
	}

	idr_remove(idr, id);

	return 0;
}