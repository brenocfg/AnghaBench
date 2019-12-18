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
struct tag {TYPE_1__* tagged; } ;
struct object_id {int dummy; } ;
struct TYPE_2__ {struct object_id oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*) ; 

struct object_id *get_tagged_oid(struct tag *tag)
{
	if (!tag->tagged)
		die("bad tag");
	return &tag->tagged->oid;
}