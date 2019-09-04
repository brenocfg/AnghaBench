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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  send_sideband (int,int,char const*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ use_sideband ; 
 int /*<<< orphan*/  write_or_die (int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xwrite (int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_client_data(int fd, const char *data, ssize_t sz)
{
	if (use_sideband) {
		send_sideband(1, fd, data, sz, use_sideband);
		return;
	}
	if (fd == 3)
		/* emergency quit */
		fd = 2;
	if (fd == 2) {
		/* XXX: are we happy to lose stuff here? */
		xwrite(fd, data, sz);
		return;
	}
	write_or_die(fd, data, sz);
}