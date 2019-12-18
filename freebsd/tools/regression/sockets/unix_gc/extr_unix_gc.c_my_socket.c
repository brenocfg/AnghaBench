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
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 int socket (int,int,int) ; 
 int /*<<< orphan*/  test ; 

__attribute__((used)) static int
my_socket(int domain, int type, int proto)
{
	int sock;

	sock = socket(domain, type, proto);
	if (sock < 0)
		err(-1, "%s: socket", test);
	return (sock);
}