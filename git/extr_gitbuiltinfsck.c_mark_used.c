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
struct object {int /*<<< orphan*/  flags; } ;
struct fsck_options {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USED ; 

__attribute__((used)) static int mark_used(struct object *obj, int type, void *data, struct fsck_options *options)
{
	if (!obj)
		return 1;
	obj->flags |= USED;
	return 0;
}