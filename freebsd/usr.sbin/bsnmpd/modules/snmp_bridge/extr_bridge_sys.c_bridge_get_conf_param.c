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
struct ifdrv {int ifd_len; int /*<<< orphan*/  ifd_cmd; struct ifbrparam* ifd_data; int /*<<< orphan*/  ifd_name; } ;
struct ifbrparam {int ifbrp_maxage; int ifbrp_hellotime; int ifbrp_fwddelay; int /*<<< orphan*/  ifbrp_csize; int /*<<< orphan*/  ifbrp_ctime; int /*<<< orphan*/  ifbrp_cexceeded; int /*<<< orphan*/  ifbrp_prio; } ;
struct bridge_if {int bridge_max_age; int bridge_hello_time; int bridge_fwd_delay; int /*<<< orphan*/  max_addrs; int /*<<< orphan*/  age_time; int /*<<< orphan*/  lrnt_drops; int /*<<< orphan*/  priority; int /*<<< orphan*/  bif_name; } ;
typedef  int /*<<< orphan*/  b_param ;

/* Variables and functions */
 int /*<<< orphan*/  BRDGGCACHE ; 
 int /*<<< orphan*/  BRDGGFD ; 
 int /*<<< orphan*/  BRDGGHT ; 
 int /*<<< orphan*/  BRDGGMA ; 
 int /*<<< orphan*/  BRDGGPRI ; 
 int /*<<< orphan*/  BRDGGRTE ; 
 int /*<<< orphan*/  BRDGGTO ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SIOCGDRVSPEC ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifdrv*) ; 
 int /*<<< orphan*/  sock ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bridge_get_conf_param(struct bridge_if *bif)
{
	struct ifdrv ifd;
	struct ifbrparam b_param;

	strlcpy(ifd.ifd_name, bif->bif_name, IFNAMSIZ);
	ifd.ifd_len = sizeof(b_param);
	ifd.ifd_data = &b_param;

	/* Bridge priority. */
	ifd.ifd_cmd = BRDGGPRI;
	if (ioctl(sock, SIOCGDRVSPEC, &ifd) < 0) {
		syslog(LOG_ERR, "update bridge: ioctl(BRDGGPRI) failed: %s",
		    strerror(errno));
		return (-1);
	}

	bif->priority = b_param.ifbrp_prio;

	/* Configured max age. */
	ifd.ifd_cmd = BRDGGMA;
	if (ioctl(sock, SIOCGDRVSPEC, &ifd) < 0) {
		syslog(LOG_ERR, "update bridge: ioctl(BRDGGMA) failed: %s",
		    strerror(errno));
		return (-1);
	}

	/* Centi-seconds. */
	bif->bridge_max_age = 100 * b_param.ifbrp_maxage;

	/* Configured hello time. */
	ifd.ifd_cmd = BRDGGHT;
	if (ioctl(sock, SIOCGDRVSPEC, &ifd) < 0) {
		syslog(LOG_ERR, "update bridge: ioctl(BRDGGHT) failed: %s",
		    strerror(errno));
		return (-1);
	}
	bif->bridge_hello_time = 100 * b_param.ifbrp_hellotime;

	/* Forward delay. */
	ifd.ifd_cmd = BRDGGFD;
	if (ioctl(sock, SIOCGDRVSPEC, &ifd) < 0) {
		syslog(LOG_ERR, "update bridge: ioctl(BRDGGFD) failed: %s",
		    strerror(errno));
		return (-1);
	}
	bif->bridge_fwd_delay = 100 * b_param.ifbrp_fwddelay;

	/* Number of dropped addresses. */
	ifd.ifd_cmd = BRDGGRTE;
	if (ioctl(sock, SIOCGDRVSPEC, &ifd) < 0) {
		syslog(LOG_ERR, "update bridge: ioctl(BRDGGRTE) failed: %s",
		    strerror(errno));
		return (-1);
	}
	bif->lrnt_drops = b_param.ifbrp_cexceeded;

	/* Address table timeout. */
	ifd.ifd_cmd = BRDGGTO;
	if (ioctl(sock, SIOCGDRVSPEC, &ifd) < 0) {
		syslog(LOG_ERR, "update bridge: ioctl(BRDGGTO) failed: %s",
		    strerror(errno));
		return (-1);
	}
	bif->age_time = b_param.ifbrp_ctime;

	/* Address table size. */
	ifd.ifd_cmd = BRDGGCACHE;
	if (ioctl(sock, SIOCGDRVSPEC, &ifd) < 0) {
		syslog(LOG_ERR, "update bridge: ioctl(BRDGGCACHE) "
		    "failed: %s", strerror(errno));
		return (-1);
	}
	bif->max_addrs = b_param.ifbrp_csize;

	return (0);
}