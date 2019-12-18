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
typedef  scalar_t__ u8 ;
struct radius_msg_list {struct radius_msg_list* next; int /*<<< orphan*/  addr; int /*<<< orphan*/  msg; } ;
struct radius_client_data {struct radius_msg_list* msgs; int /*<<< orphan*/  ctx; int /*<<< orphan*/  next_radius_identifier; } ;
struct TYPE_2__ {scalar_t__ identifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOSTAPD_LEVEL_DEBUG ; 
 int /*<<< orphan*/  HOSTAPD_MODULE_RADIUS ; 
 int /*<<< orphan*/  hostapd_logger (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  radius_client_msg_free (struct radius_msg_list*) ; 
 TYPE_1__* radius_msg_get_hdr (int /*<<< orphan*/ ) ; 

u8 radius_client_get_id(struct radius_client_data *radius)
{
	struct radius_msg_list *entry, *prev, *_remove;
	u8 id = radius->next_radius_identifier++;

	/* remove entries with matching id from retransmit list to avoid
	 * using new reply from the RADIUS server with an old request */
	entry = radius->msgs;
	prev = NULL;
	while (entry) {
		if (radius_msg_get_hdr(entry->msg)->identifier == id) {
			hostapd_logger(radius->ctx, entry->addr,
				       HOSTAPD_MODULE_RADIUS,
				       HOSTAPD_LEVEL_DEBUG,
				       "Removing pending RADIUS message, "
				       "since its id (%d) is reused", id);
			if (prev)
				prev->next = entry->next;
			else
				radius->msgs = entry->next;
			_remove = entry;
		} else {
			_remove = NULL;
			prev = entry;
		}
		entry = entry->next;

		if (_remove)
			radius_client_msg_free(_remove);
	}

	return id;
}