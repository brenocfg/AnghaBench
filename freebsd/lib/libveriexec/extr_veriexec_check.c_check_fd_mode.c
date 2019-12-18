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
struct stat {unsigned int st_mode; } ;

/* Variables and functions */
 int EAUTH ; 
 int errno ; 
 scalar_t__ fstat (int,struct stat*) ; 

__attribute__((used)) static int
check_fd_mode(int fd, unsigned int mask)
{
	struct stat st;

	if (fstat(fd, &st) < 0)
		return errno;

	if ((st.st_mode & mask) == 0)
		return EAUTH;

	return 0;
}