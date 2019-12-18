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
struct xenbus_device {scalar_t__ data; int /*<<< orphan*/  nodename; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_pdev (scalar_t__) ; 

__attribute__((used)) static int
pcifront_remove(struct xenbus_device *xdev)
{
	DPRINTF("removing xenbus device node (%s)\n", xdev->nodename);
	if (xdev->data)
		put_pdev(xdev->data);
	return 0;
}