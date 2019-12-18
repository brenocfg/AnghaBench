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
struct TYPE_2__ {int length; } ;
struct rsocket {struct rs_iomap_mr* remote_iomappings; TYPE_1__ remote_iomap; } ;
struct rs_iomap_mr {int index; int /*<<< orphan*/  mr; } ;

/* Variables and functions */
 struct rs_iomap_mr* calloc (int,int) ; 

__attribute__((used)) static struct rs_iomap_mr *rs_get_iomap_mr(struct rsocket *rs)
{
	int i;

	if (!rs->remote_iomappings) {
		rs->remote_iomappings = calloc(rs->remote_iomap.length,
					       sizeof(*rs->remote_iomappings));
		if (!rs->remote_iomappings)
			return NULL;

		for (i = 0; i < rs->remote_iomap.length; i++)
			rs->remote_iomappings[i].index = i;
	}

	for (i = 0; i < rs->remote_iomap.length; i++) {
		if (!rs->remote_iomappings[i].mr)
			return &rs->remote_iomappings[i];
	}
	return NULL;
}