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
struct xenbus_device_ivars {int /*<<< orphan*/  xd_node; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/ * FALSE ; 
 int /*<<< orphan*/  M_TEMP ; 
 scalar_t__ device_get_children (int /*<<< orphan*/ *,int /*<<< orphan*/ ***,int*) ; 
 struct xenbus_device_ivars* device_get_ivars (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static device_t
xenbusb_device_exists(device_t dev, const char *node)
{
	device_t *kids;
	device_t result;
	struct xenbus_device_ivars *ivars;
	int i, count;

	if (device_get_children(dev, &kids, &count))
		return (FALSE);

	result = NULL;
	for (i = 0; i < count; i++) {
		ivars = device_get_ivars(kids[i]);
		if (!strcmp(ivars->xd_node, node)) {
			result = kids[i];
			break;
		}
	}
	free(kids, M_TEMP);

	return (result);
}