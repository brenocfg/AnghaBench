#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
typedef  TYPE_1__* profile_p ;
typedef  int /*<<< orphan*/ * profile_attr_create_p ;
typedef  TYPE_2__* attr_p ;
struct TYPE_5__ {scalar_t__ attr; int /*<<< orphan*/ * create; } ;
struct TYPE_4__ {int /*<<< orphan*/  attrs; } ;

/* Variables and functions */

profile_attr_create_p
profile_get_attr(const profile_p profile, uint16_t attr)
{
	attr_p	ad = (attr_p) profile->attrs;

	for (; ad->create != NULL; ad ++)
		if (ad->attr == attr)
			return (ad->create);

	return (NULL);
}