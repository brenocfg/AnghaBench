#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t altroot_len; } ;
typedef  TYPE_1__ libbe_handle_t ;

/* Variables and functions */

char *
be_mountpoint_augmented(libbe_handle_t *lbh, char *mountpoint)
{

	if (lbh->altroot_len == 0)
		return (mountpoint);
	if (mountpoint == NULL || *mountpoint == '\0')
		return (mountpoint);

	if (mountpoint[lbh->altroot_len] == '\0') {
		*(mountpoint + 1) = '\0';
		return (mountpoint);
	} else
		return (mountpoint + lbh->altroot_len);
}