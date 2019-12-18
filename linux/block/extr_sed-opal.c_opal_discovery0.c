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
struct opal_dev {int /*<<< orphan*/  comid; int /*<<< orphan*/  resp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IO_BUFFER_LENGTH ; 
 int /*<<< orphan*/  OPAL_DISCOVERY_COMID ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int opal_discovery0_end (struct opal_dev*) ; 
 int opal_recv_cmd (struct opal_dev*) ; 

__attribute__((used)) static int opal_discovery0(struct opal_dev *dev, void *data)
{
	int ret;

	memset(dev->resp, 0, IO_BUFFER_LENGTH);
	dev->comid = OPAL_DISCOVERY_COMID;
	ret = opal_recv_cmd(dev);
	if (ret)
		return ret;

	return opal_discovery0_end(dev);
}