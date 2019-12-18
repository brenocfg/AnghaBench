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
struct socket_info {struct socket_info* tmp_path; struct socket_info* peername; struct socket_info* myname; struct socket_info* path; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWRAP_CLOSE_ACK ; 
 int /*<<< orphan*/  SWRAP_CLOSE_RECV ; 
 int /*<<< orphan*/  SWRAP_CLOSE_SEND ; 
 int /*<<< orphan*/  SWRAP_DLIST_REMOVE (int /*<<< orphan*/ ,struct socket_info*) ; 
 struct socket_info* find_socket_info (int) ; 
 int /*<<< orphan*/  free (struct socket_info*) ; 
 int real_close (int) ; 
 int /*<<< orphan*/  sockets ; 
 int /*<<< orphan*/  swrap_dump_packet (struct socket_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (struct socket_info*) ; 

int swrap_close(int fd)
{
	struct socket_info *si = find_socket_info(fd);
	int ret;

	if (!si) {
		return real_close(fd);
	}

	SWRAP_DLIST_REMOVE(sockets, si);

	if (si->myname && si->peername) {
		swrap_dump_packet(si, NULL, SWRAP_CLOSE_SEND, NULL, 0);
	}

	ret = real_close(fd);

	if (si->myname && si->peername) {
		swrap_dump_packet(si, NULL, SWRAP_CLOSE_RECV, NULL, 0);
		swrap_dump_packet(si, NULL, SWRAP_CLOSE_ACK, NULL, 0);
	}

	if (si->path) free(si->path);
	if (si->myname) free(si->myname);
	if (si->peername) free(si->peername);
	if (si->tmp_path) {
		unlink(si->tmp_path);
		free(si->tmp_path);
	}
	free(si);

	return ret;
}