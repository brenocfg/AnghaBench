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
struct devfs_dirent {TYPE_1__* de_cdp; } ;
struct cdev {int dummy; } ;
struct TYPE_2__ {int cdp_flags; struct cdev cdp_c; } ;

/* Variables and functions */
 int CDP_ACTIVE ; 

__attribute__((used)) static struct cdev *
devfs_rule_getdev(struct devfs_dirent *de)
{

	if (de->de_cdp == NULL)
		return (NULL);
	if (de->de_cdp->cdp_flags & CDP_ACTIVE)
		return (&de->de_cdp->cdp_c);
	else
		return (NULL);
}