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
typedef  int uint32_t ;
struct ifdrv {int ifd_len; struct ifbifconf* ifd_data; int /*<<< orphan*/  ifd_cmd; int /*<<< orphan*/  ifd_name; } ;
struct ifbreq {int dummy; } ;
struct ifbifconf {int ifbic_len; struct ifbreq* ifbic_req; } ;
struct bridge_if {int /*<<< orphan*/  bif_name; } ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  ifbc ;

/* Variables and functions */
 int /*<<< orphan*/  BRDGGIFS ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SIOCGDRVSPEC ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct ifbreq*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifdrv*) ; 
 scalar_t__ realloc (struct ifbreq*,int) ; 
 int /*<<< orphan*/  sock ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
bridge_port_get_iflist(struct bridge_if *bif, struct ifbreq **buf)
{
	int n = 128;
	uint32_t len;
	struct ifbreq *ninbuf;
	struct ifbifconf ifbc;
	struct ifdrv ifd;

	*buf = NULL;
	strlcpy(ifd.ifd_name, bif->bif_name, IFNAMSIZ);
	ifd.ifd_cmd = BRDGGIFS;
	ifd.ifd_len = sizeof(ifbc);
	ifd.ifd_data = &ifbc;

	for ( ; ; ) {
		len = n * sizeof(struct ifbreq);
		if ((ninbuf = (struct ifbreq *)realloc(*buf, len)) == NULL) {
			syslog(LOG_ERR, "get bridge member list: "
			    "realloc failed: %s", strerror(errno));
			free(*buf);
			*buf = NULL;
			return (-1);
		}

		ifbc.ifbic_len = len;
		ifbc.ifbic_req = *buf = ninbuf;

		if (ioctl(sock, SIOCGDRVSPEC, &ifd) < 0) {
			syslog(LOG_ERR, "get bridge member list: ioctl "
			    "(BRDGGIFS) failed: %s", strerror(errno));
			free(*buf);
			buf = NULL;
			return (-1);
		}

		if ((ifbc.ifbic_len + sizeof(struct ifbreq)) < len)
			break;

		n += 64;
	}

	return (ifbc.ifbic_len);
}