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
struct transport {struct git_transport_data* data; } ;
struct git_transport_data {scalar_t__ conn; int /*<<< orphan*/ * fd; scalar_t__ got_remote_heads; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_connect (scalar_t__) ; 
 int /*<<< orphan*/  free (struct git_transport_data*) ; 
 int /*<<< orphan*/  packet_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int disconnect_git(struct transport *transport)
{
	struct git_transport_data *data = transport->data;
	if (data->conn) {
		if (data->got_remote_heads)
			packet_flush(data->fd[1]);
		close(data->fd[0]);
		close(data->fd[1]);
		finish_connect(data->conn);
	}

	free(data);
	return 0;
}