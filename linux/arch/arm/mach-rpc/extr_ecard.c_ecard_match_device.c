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
struct TYPE_2__ {int manufacturer; scalar_t__ product; } ;
struct expansion_card {TYPE_1__ cid; } ;
struct ecard_id {int manufacturer; scalar_t__ product; } ;

/* Variables and functions */

__attribute__((used)) static const struct ecard_id *
ecard_match_device(const struct ecard_id *ids, struct expansion_card *ec)
{
	int i;

	for (i = 0; ids[i].manufacturer != 65535; i++)
		if (ec->cid.manufacturer == ids[i].manufacturer &&
		    ec->cid.product == ids[i].product)
			return ids + i;

	return NULL;
}