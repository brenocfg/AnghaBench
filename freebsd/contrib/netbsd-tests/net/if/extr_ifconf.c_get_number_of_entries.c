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
struct ifreq {int dummy; } ;
struct ifconf {int ifc_len; int /*<<< orphan*/ * ifc_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  SIOCGIFCONF ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct ifconf*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_number_of_entries(void)
{
	int fd, r;
	struct ifconf ifc;

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd == -1)
		err(EXIT_FAILURE, "socket");

	ifc.ifc_len = 0;
	ifc.ifc_buf = NULL;

	r = ioctl(fd, SIOCGIFCONF, &ifc);
	if (r == -1)
		err(EXIT_FAILURE, "ioctl");

	close(fd);

	return ifc.ifc_len / sizeof(struct ifreq);
}