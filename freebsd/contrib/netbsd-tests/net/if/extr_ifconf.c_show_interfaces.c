#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  sa_len; int /*<<< orphan*/  sa_family; } ;
struct ifreq {char* ifr_name; TYPE_1__ ifr_addr; } ;
struct ifconf {int ifc_len; struct ifreq* ifc_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  SIOCGIFCONF ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (struct ifreq*) ; 
 int get_number_of_entries () ; 
 int ioctl (int,int /*<<< orphan*/ ,struct ifconf*) ; 
 struct ifreq* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
show_interfaces(int nifreqs)
{
	int i, fd, r;
	struct ifconf ifc;
	struct ifreq *ifreqs;

	if (nifreqs == 0)
		nifreqs = get_number_of_entries();

	if (nifreqs <= 0)
		errx(EXIT_FAILURE, "nifreqs=%d", nifreqs);

	ifreqs = malloc(sizeof(struct ifreq) * nifreqs);
	if (ifreqs == NULL)
		err(EXIT_FAILURE, "malloc(sizeof(ifreq) * %d)", nifreqs);

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd == -1)
		err(EXIT_FAILURE, "socket");

	ifc.ifc_len = sizeof(struct ifreq) * nifreqs;
	ifc.ifc_req = ifreqs;

	r = ioctl(fd, SIOCGIFCONF, &ifc);
	if (r == -1)
		err(EXIT_FAILURE, "ioctl");
	close(fd);

	for (i=0; i < (int)(ifc.ifc_len / sizeof(struct ifreq)); i++) {
		printf("%s: af=%hhu socklen=%hhu\n", ifreqs[i].ifr_name,
		    ifreqs[i].ifr_addr.sa_family, ifreqs[i].ifr_addr.sa_len);
	}

	free(ifreqs);
}