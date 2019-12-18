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
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 short EV_ET ; 
 short last_read_notification_was_et ; 
 int /*<<< orphan*/  read_notification_count ; 

__attribute__((used)) static void
read_notification_cb(evutil_socket_t fd, short event, void *arg)
{
	read_notification_count++;
	last_read_notification_was_et = (event & EV_ET);
}