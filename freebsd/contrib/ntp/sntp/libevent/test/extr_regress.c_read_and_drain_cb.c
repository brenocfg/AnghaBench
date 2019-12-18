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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  n_read_and_drain_cb ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
read_and_drain_cb(evutil_socket_t fd, short what, void *arg)
{
	char buf[128];
	int n;
	++n_read_and_drain_cb;
	while ((n = read(fd, buf, sizeof(buf))) > 0)
		;
}