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
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  n_write_a_byte_cb ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
write_a_byte_cb(evutil_socket_t fd, short what, void *arg)
{
	char buf[] = "x";
	if (write(fd, buf, 1) == 1)
		++n_write_a_byte_cb;
}