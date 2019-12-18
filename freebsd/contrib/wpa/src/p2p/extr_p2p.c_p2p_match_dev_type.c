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
struct wps_parse_attr {scalar_t__ num_req_dev_type; int /*<<< orphan*/  req_dev_type; } ;
struct wpabuf {int dummy; } ;
struct p2p_data {TYPE_1__* cfg; } ;
struct TYPE_2__ {size_t num_sec_dev_types; int /*<<< orphan*/ * sec_dev_type; int /*<<< orphan*/  pri_dev_type; } ;

/* Variables and functions */
 scalar_t__ dev_type_list_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ wps_parse_msg (struct wpabuf*,struct wps_parse_attr*) ; 

int p2p_match_dev_type(struct p2p_data *p2p, struct wpabuf *wps)
{
	struct wps_parse_attr attr;
	size_t i;

	if (wps_parse_msg(wps, &attr))
		return 1; /* assume no Requested Device Type attributes */

	if (attr.num_req_dev_type == 0)
		return 1; /* no Requested Device Type attributes -> match */

	if (dev_type_list_match(p2p->cfg->pri_dev_type, attr.req_dev_type,
				attr.num_req_dev_type))
		return 1; /* Own Primary Device Type matches */

	for (i = 0; i < p2p->cfg->num_sec_dev_types; i++) {
		if (dev_type_list_match(p2p->cfg->sec_dev_type[i],
					attr.req_dev_type,
					attr.num_req_dev_type))
			return 1; /* Own Secondary Device Type matches */
	}

	/* No matching device type found */
	return 0;
}