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
struct radius_msg_list {scalar_t__ next_try; struct radius_msg_list* next; } ;
struct radius_client_data {int /*<<< orphan*/  ctx; struct radius_msg_list* msgs; } ;
struct os_reltime {scalar_t__ sec; } ;
typedef  scalar_t__ os_time_t ;

/* Variables and functions */
 int /*<<< orphan*/  HOSTAPD_LEVEL_DEBUG ; 
 int /*<<< orphan*/  HOSTAPD_MODULE_RADIUS ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct radius_client_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct radius_client_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hostapd_logger (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,long) ; 
 int /*<<< orphan*/  os_get_reltime (struct os_reltime*) ; 
 int /*<<< orphan*/  radius_client_timer ; 

__attribute__((used)) static void radius_client_update_timeout(struct radius_client_data *radius)
{
	struct os_reltime now;
	os_time_t first;
	struct radius_msg_list *entry;

	eloop_cancel_timeout(radius_client_timer, radius, NULL);

	if (radius->msgs == NULL) {
		return;
	}

	first = 0;
	for (entry = radius->msgs; entry; entry = entry->next) {
		if (first == 0 || entry->next_try < first)
			first = entry->next_try;
	}

	os_get_reltime(&now);
	if (first < now.sec)
		first = now.sec;
	eloop_register_timeout(first - now.sec, 0, radius_client_timer, radius,
			       NULL);
	hostapd_logger(radius->ctx, NULL, HOSTAPD_MODULE_RADIUS,
		       HOSTAPD_LEVEL_DEBUG, "Next RADIUS client retransmit in"
		       " %ld seconds", (long int) (first - now.sec));
}