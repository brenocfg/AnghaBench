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
struct socket_info {int fd; } ;

/* Variables and functions */
 int dup_internal (struct socket_info*,int) ; 
 struct socket_info* find_socket_info (int) ; 
 int real_dup (int) ; 

int swrap_dup(int oldd)
{
	struct socket_info *si;
	int fd;

	si = find_socket_info(oldd);
	if (si == NULL)
		return real_dup(oldd);

	fd = real_dup(si->fd);
	if (fd < 0)
		return fd;

	return dup_internal(si, fd);
}