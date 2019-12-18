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
typedef  scalar_t__ uint8_t ;
struct ifdrv {int ifd_len; int /*<<< orphan*/  ifd_cmd; struct ifbreq* ifd_data; int /*<<< orphan*/  ifd_name; } ;
struct ifbreq {scalar_t__ ifbr_priority; int /*<<< orphan*/  ifbr_ifsname; } ;
struct bridge_port {char const* p_name; scalar_t__ priority; } ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  b_req ;

/* Variables and functions */
 int /*<<< orphan*/  BRDGSIFPRIO ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SIOCSDRVSPEC ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifdrv*) ; 
 int /*<<< orphan*/  sock ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 

int
bridge_port_set_priority(const char *bif_name, struct bridge_port *bp,
	int32_t priority)
{
	struct ifdrv ifd;
	struct ifbreq b_req;

	strlcpy(ifd.ifd_name, bif_name, sizeof(ifd.ifd_name));
	ifd.ifd_len = sizeof(b_req);
	ifd.ifd_data = &b_req;
	strlcpy(b_req.ifbr_ifsname, bp->p_name, sizeof(b_req.ifbr_ifsname));

	b_req.ifbr_priority = (uint8_t) priority;
	ifd.ifd_cmd = BRDGSIFPRIO;

	if (ioctl(sock, SIOCSDRVSPEC, &ifd) < 0) {
		syslog(LOG_ERR, "set member %s param: ioctl(BRDGSIFPRIO) "
		    "failed: %s", bp->p_name, strerror(errno));
		return (-1);
	}

	bp->priority = priority;
	return (0);
}