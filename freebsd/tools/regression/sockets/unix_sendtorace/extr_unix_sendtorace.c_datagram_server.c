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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 scalar_t__ recv (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static void
datagram_server(int serverfd)
{
	ssize_t len;
	char c;

	while (1) {
		len = recv(serverfd, &c, sizeof(c), 0);
		if (len < 0)
			warn("datagram_server: recv");
	}
}