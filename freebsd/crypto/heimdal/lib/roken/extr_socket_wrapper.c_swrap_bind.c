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
struct socket_info {int myname_len; int bound; int /*<<< orphan*/  bcast; int /*<<< orphan*/  myname; } ;
struct sockaddr_un {int /*<<< orphan*/  sun_path; } ;
typedef  struct sockaddr const sockaddr ;
typedef  int socklen_t ;

/* Variables and functions */
 struct socket_info* find_socket_info (int) ; 
 int real_bind (int,struct sockaddr const*,int) ; 
 int sockaddr_convert_to_un (struct socket_info*,struct sockaddr const*,int,struct sockaddr_un*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sockaddr_dup (struct sockaddr const*,int) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

int swrap_bind(int s, const struct sockaddr *myaddr, socklen_t addrlen)
{
	int ret;
	struct sockaddr_un un_addr;
	struct socket_info *si = find_socket_info(s);

	if (!si) {
		return real_bind(s, myaddr, addrlen);
	}

	si->myname_len = addrlen;
	si->myname = sockaddr_dup(myaddr, addrlen);

	ret = sockaddr_convert_to_un(si, (const struct sockaddr *)myaddr, addrlen, &un_addr, 1, &si->bcast);
	if (ret == -1) return -1;

	unlink(un_addr.sun_path);

	ret = real_bind(s, (struct sockaddr *)&un_addr,
			sizeof(struct sockaddr_un));

	if (ret == 0) {
		si->bound = 1;
	}

	return ret;
}