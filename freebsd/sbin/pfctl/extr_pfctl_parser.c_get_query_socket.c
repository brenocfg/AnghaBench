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
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  get_socket_domain () ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
get_query_socket(void)
{
	static int s = -1;

	if (s == -1) {
		if ((s = socket(get_socket_domain(), SOCK_DGRAM, 0)) == -1)
			err(1, "socket");
	}

	return (s);
}