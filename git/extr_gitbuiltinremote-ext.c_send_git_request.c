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

/* Variables and functions */
 int /*<<< orphan*/  packet_write_fmt (int,char*,char const*,char const*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void send_git_request(int stdin_fd, const char *serv, const char *repo,
	const char *vhost)
{
	if (!vhost)
		packet_write_fmt(stdin_fd, "%s %s%c", serv, repo, 0);
	else
		packet_write_fmt(stdin_fd, "%s %s%chost=%s%c", serv, repo, 0,
			     vhost, 0);
}