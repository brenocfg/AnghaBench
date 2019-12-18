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
typedef  int /*<<< orphan*/  dummyif ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  SIOCSNDFLUSH_IN6 ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

__attribute__((used)) static void
harmonize_rtr()
{
	char dummyif[IFNAMSIZ+8];
	int sock;

	if ((sock = socket(AF_INET6, SOCK_DGRAM, 0)) < 0)
		err(1, "socket");
	strlcpy(dummyif, "lo0", sizeof(dummyif)); /* dummy */
	if (ioctl(sock, SIOCSNDFLUSH_IN6, (caddr_t)&dummyif) < 0)
		err(1, "ioctl(SIOCSNDFLUSH_IN6)");

	close(sock);
}