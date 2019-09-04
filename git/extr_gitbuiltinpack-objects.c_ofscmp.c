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
struct in_pack_object {scalar_t__ offset; TYPE_1__* object; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int oidcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ofscmp(const void *a_, const void *b_)
{
	struct in_pack_object *a = (struct in_pack_object *)a_;
	struct in_pack_object *b = (struct in_pack_object *)b_;

	if (a->offset < b->offset)
		return -1;
	else if (a->offset > b->offset)
		return 1;
	else
		return oidcmp(&a->object->oid, &b->object->oid);
}