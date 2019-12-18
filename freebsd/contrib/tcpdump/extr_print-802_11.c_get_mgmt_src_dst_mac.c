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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u_char ;
struct mgmt_header_t {int /*<<< orphan*/ * da; int /*<<< orphan*/ * sa; } ;

/* Variables and functions */

__attribute__((used)) static void
get_mgmt_src_dst_mac(const u_char *p, const uint8_t **srcp, const uint8_t **dstp)
{
	const struct mgmt_header_t *hp = (const struct mgmt_header_t *) p;

	if (srcp != NULL)
		*srcp = hp->sa;
	if (dstp != NULL)
		*dstp = hp->da;
}