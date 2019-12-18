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
struct drbd_thread {struct drbd_connection* connection; } ;
struct drbd_connection {int /*<<< orphan*/  receiver_plug; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_HARD ; 
 int /*<<< orphan*/  C_DISCONNECTING ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  NS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_finish_plug (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_start_plug (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conn ; 
 int conn_connect (struct drbd_connection*) ; 
 int /*<<< orphan*/  conn_disconnect (struct drbd_connection*) ; 
 int /*<<< orphan*/  conn_request_state (struct drbd_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbd_info (struct drbd_connection*,char*) ; 
 int /*<<< orphan*/  drbd_warn (struct drbd_connection*,char*) ; 
 int /*<<< orphan*/  drbdd (struct drbd_connection*) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int /*<<< orphan*/ ) ; 

int drbd_receiver(struct drbd_thread *thi)
{
	struct drbd_connection *connection = thi->connection;
	int h;

	drbd_info(connection, "receiver (re)started\n");

	do {
		h = conn_connect(connection);
		if (h == 0) {
			conn_disconnect(connection);
			schedule_timeout_interruptible(HZ);
		}
		if (h == -1) {
			drbd_warn(connection, "Discarding network configuration.\n");
			conn_request_state(connection, NS(conn, C_DISCONNECTING), CS_HARD);
		}
	} while (h == 0);

	if (h > 0) {
		blk_start_plug(&connection->receiver_plug);
		drbdd(connection);
		blk_finish_plug(&connection->receiver_plug);
	}

	conn_disconnect(connection);

	drbd_info(connection, "receiver terminated\n");
	return 0;
}