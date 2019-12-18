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
struct ifdrv {int ifd_len; struct ifbpstpconf* ifd_data; int /*<<< orphan*/  ifd_cmd; int /*<<< orphan*/  ifd_name; } ;
struct ifbpstpreq {int dummy; } ;
struct ifbpstpconf {int ifbpstp_len; struct ifbpstpreq* ifbpstp_req; } ;
struct bridge_if {int /*<<< orphan*/  bif_name; } ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  ifbstp ;

/* Variables and functions */
 int /*<<< orphan*/  BRDGGIFSSTP ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SIOCGDRVSPEC ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct ifbpstpreq*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifdrv*) ; 
 scalar_t__ realloc (struct ifbpstpreq*,int) ; 
 int /*<<< orphan*/  sock ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
bridge_port_get_ifstplist(struct bridge_if *bif, struct ifbpstpreq **buf)
{
	int n = 128;
	uint32_t len;
	struct ifbpstpreq *ninbuf;
	struct ifbpstpconf ifbstp;
	struct ifdrv ifd;

	*buf = NULL;
	strlcpy(ifd.ifd_name, bif->bif_name, IFNAMSIZ);
	ifd.ifd_cmd = BRDGGIFSSTP;
	ifd.ifd_len = sizeof(ifbstp);
	ifd.ifd_data = &ifbstp;

	for ( ; ; ) {
		len = n * sizeof(struct ifbpstpreq);
		if ((ninbuf = (struct ifbpstpreq *)
		    realloc(*buf, len)) == NULL) {
			syslog(LOG_ERR, "get bridge STP ports list: "
			    "realloc failed: %s", strerror(errno));
			free(*buf);
			*buf = NULL;
			return (-1);
		}

		ifbstp.ifbpstp_len = len;
		ifbstp.ifbpstp_req = *buf = ninbuf;

		if (ioctl(sock, SIOCGDRVSPEC, &ifd) < 0) {
			syslog(LOG_ERR, "get bridge STP ports list: ioctl "
			    "(BRDGGIFSSTP) failed: %s", strerror(errno));
			free(*buf);
			buf = NULL;
			return (-1);
		}

		if ((ifbstp.ifbpstp_len + sizeof(struct ifbpstpreq)) < len)
			break;

		n += 64;
	}

	return (ifbstp.ifbpstp_len);
}