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
struct packet_info {int dummy; } ;
struct drbd_connection {int dummy; } ;

/* Variables and functions */
 int drbd_send_ping_ack (struct drbd_connection*) ; 

__attribute__((used)) static int got_Ping(struct drbd_connection *connection, struct packet_info *pi)
{
	return drbd_send_ping_ack(connection);

}