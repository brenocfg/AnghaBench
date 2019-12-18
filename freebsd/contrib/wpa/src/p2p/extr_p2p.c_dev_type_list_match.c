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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 scalar_t__ dev_type_match (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

int dev_type_list_match(const u8 *dev_type, const u8 *req_dev_type[],
			size_t num_req_dev_type)
{
	size_t i;
	for (i = 0; i < num_req_dev_type; i++) {
		if (dev_type_match(dev_type, req_dev_type[i]))
			return 1;
	}
	return 0;
}