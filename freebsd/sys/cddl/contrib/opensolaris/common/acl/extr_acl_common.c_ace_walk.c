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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  a_access_mask; int /*<<< orphan*/  a_type; int /*<<< orphan*/  a_flags; } ;
typedef  TYPE_1__ ace_t ;

/* Variables and functions */

uint64_t
ace_walk(void *datap, uint64_t cookie, int aclcnt, uint16_t *flags,
    uint16_t *type, uint32_t *mask)
{
	ace_t *acep = datap;

	if (cookie >= aclcnt)
		return (0);

	*flags = acep[cookie].a_flags;
	*type = acep[cookie].a_type;
	*mask = acep[cookie++].a_access_mask;

	return (cookie);
}