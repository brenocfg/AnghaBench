#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ dlen; int /*<<< orphan*/  data; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ object_data ;
struct TYPE_6__ {scalar_t__ type; scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ git_rawobj ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 scalar_t__ git_object_string2type (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void cmp_objects(git_rawobj *o, object_data *d)
{
	cl_assert(o->type == git_object_string2type(d->type));
	cl_assert(o->len == d->dlen);

	if (o->len > 0)
		cl_assert(memcmp(o->data, d->data, o->len) == 0);
}