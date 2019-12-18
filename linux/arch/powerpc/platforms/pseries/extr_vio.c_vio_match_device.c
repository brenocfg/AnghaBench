#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vio_device_id {char* type; int /*<<< orphan*/  compat; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct vio_dev {TYPE_1__ dev; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ of_device_is_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct vio_device_id *vio_match_device(
		const struct vio_device_id *ids, const struct vio_dev *dev)
{
	while (ids->type[0] != '\0') {
		if ((strncmp(dev->type, ids->type, strlen(ids->type)) == 0) &&
		    of_device_is_compatible(dev->dev.of_node,
					 ids->compat))
			return ids;
		ids++;
	}
	return NULL;
}