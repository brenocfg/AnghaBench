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
struct stat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,int,int,int) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int socket (int,int,int) ; 

__attribute__((used)) static void
dotest(int domain, int type, int protocol)
{
	struct stat sb;
	int sock;

	sock = socket(domain, type, protocol);
	if (sock < 0)
		err(-1, "socket(%d, %d, %d)", domain, type, protocol);

	if (fstat(sock, &sb) < 0)
		err(-1, "fstat on socket(%d, %d, %d)", domain, type,
		    protocol);

	close(sock);
}