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
struct devreq {int /*<<< orphan*/  dr_name; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  EVENTHANDLER_DIRECT_INVOKE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dev_lookup ; 
 int /*<<< orphan*/ * device_lookup_by_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * memchr (int /*<<< orphan*/ ,char,int) ; 

__attribute__((used)) static int
find_device(struct devreq *req, device_t *devp)
{
	device_t dev;

	/*
	 * First, ensure that the name is nul terminated.
	 */
	if (memchr(req->dr_name, '\0', sizeof(req->dr_name)) == NULL)
		return (EINVAL);

	/*
	 * Second, try to find an attached device whose name matches
	 * 'name'.
	 */
	dev = device_lookup_by_name(req->dr_name);
	if (dev != NULL) {
		*devp = dev;
		return (0);
	}

	/* Finally, give device enumerators a chance. */
	dev = NULL;
	EVENTHANDLER_DIRECT_INVOKE(dev_lookup, req->dr_name, &dev);
	if (dev == NULL)
		return (ENOENT);
	*devp = dev;
	return (0);
}