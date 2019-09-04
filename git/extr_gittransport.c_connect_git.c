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
struct transport {int /*<<< orphan*/  url; struct git_transport_data* data; } ;
struct git_transport_data {int* fd; int /*<<< orphan*/  conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  git_connect (int*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int connect_git(struct transport *transport, const char *name,
		       const char *executable, int fd[2])
{
	struct git_transport_data *data = transport->data;
	data->conn = git_connect(data->fd, transport->url,
				 executable, 0);
	fd[0] = data->fd[0];
	fd[1] = data->fd[1];
	return 0;
}