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
struct socket_info {int fd; struct socket_info* next; } ;

/* Variables and functions */
 struct socket_info* sockets ; 

__attribute__((used)) static struct socket_info *find_socket_info(int fd)
{
	struct socket_info *i;
	for (i = sockets; i; i = i->next) {
		if (i->fd == fd)
			return i;
	}

	return NULL;
}