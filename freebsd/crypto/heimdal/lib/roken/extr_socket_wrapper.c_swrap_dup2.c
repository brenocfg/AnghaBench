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
 int real_dup2 (int,int) ; 
 int /*<<< orphan*/  swrap_close (int) ; 

int swrap_dup2(int oldd, int newd)
{
	struct socket_info *si_newd, *si_oldd;
	int fd;

	if (newd == oldd)
	    return newd;

	si_oldd = find_socket_info(oldd);
	si_newd = find_socket_info(newd);

	if (si_oldd == NULL && si_newd == NULL)
		return real_dup2(oldd, newd);

	fd = real_dup2(si_oldd->fd, newd);
	if (fd < 0)
		return fd;

	/* close new socket first */
	if (si_newd)
	       	swrap_close(newd);

	return dup_internal(si_oldd, fd);
}