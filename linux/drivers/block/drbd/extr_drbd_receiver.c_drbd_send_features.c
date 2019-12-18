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
struct p_connection_features {void* feature_flags; void* protocol_max; void* protocol_min; } ;
struct drbd_socket {int dummy; } ;
struct drbd_connection {struct drbd_socket data; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PRO_FEATURES ; 
 int /*<<< orphan*/  PRO_VERSION_MAX ; 
 int /*<<< orphan*/  PRO_VERSION_MIN ; 
 int /*<<< orphan*/  P_CONNECTION_FEATURES ; 
 struct p_connection_features* conn_prepare_command (struct drbd_connection*,struct drbd_socket*) ; 
 int conn_send_command (struct drbd_connection*,struct drbd_socket*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct p_connection_features*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int drbd_send_features(struct drbd_connection *connection)
{
	struct drbd_socket *sock;
	struct p_connection_features *p;

	sock = &connection->data;
	p = conn_prepare_command(connection, sock);
	if (!p)
		return -EIO;
	memset(p, 0, sizeof(*p));
	p->protocol_min = cpu_to_be32(PRO_VERSION_MIN);
	p->protocol_max = cpu_to_be32(PRO_VERSION_MAX);
	p->feature_flags = cpu_to_be32(PRO_FEATURES);
	return conn_send_command(connection, sock, P_CONNECTION_FEATURES, sizeof(*p), NULL, 0);
}