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
 int /*<<< orphan*/  UNUSED_ARG (int) ; 
 int /*<<< orphan*/  init_socket_sig (int) ; 
 int /*<<< orphan*/  maintain_activefds (int,int) ; 

__attribute__((used)) static void
ntpd_addremove_io_fd(
	int	fd,
	int	is_pipe,
	int	remove_it
	)
{
	UNUSED_ARG(is_pipe);

#ifdef HAVE_SIGNALED_IO
	if (!remove_it)
		init_socket_sig(fd);
#endif /* not HAVE_SIGNALED_IO */

	maintain_activefds(fd, remove_it);
}