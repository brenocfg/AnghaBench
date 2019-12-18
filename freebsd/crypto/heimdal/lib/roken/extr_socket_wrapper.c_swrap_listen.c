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
struct socket_info {int dummy; } ;

/* Variables and functions */
 struct socket_info* find_socket_info (int) ; 
 int real_listen (int,int) ; 

int swrap_listen(int s, int backlog)
{
	int ret;
	struct socket_info *si = find_socket_info(s);

	if (!si) {
		return real_listen(s, backlog);
	}

	ret = real_listen(s, backlog);

	return ret;
}