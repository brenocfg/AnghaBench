#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct table_info {int dummy; } ;
struct numarray {int /*<<< orphan*/  value; int /*<<< orphan*/  number; } ;
struct TYPE_6__ {int /*<<< orphan*/  kidx; } ;
struct TYPE_5__ {int /*<<< orphan*/  key; } ;
struct TYPE_7__ {TYPE_2__ v; TYPE_1__ k; } ;
typedef  TYPE_3__ ipfw_obj_tentry ;

/* Variables and functions */

__attribute__((used)) static int
ta_dump_numarray_tentry(void *ta_state, struct table_info *ti, void *e,
    ipfw_obj_tentry *tent)
{
	struct numarray *na;

	na = (struct numarray *)e;

	tent->k.key = na->number;
	tent->v.kidx = na->value;

	return (0);
}