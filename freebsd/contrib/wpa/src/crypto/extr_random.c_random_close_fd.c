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
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  eloop_unregister_read_sock (int) ; 
 int random_fd ; 

__attribute__((used)) static void random_close_fd(void)
{
	if (random_fd >= 0) {
		eloop_unregister_read_sock(random_fd);
		close(random_fd);
		random_fd = -1;
	}
}