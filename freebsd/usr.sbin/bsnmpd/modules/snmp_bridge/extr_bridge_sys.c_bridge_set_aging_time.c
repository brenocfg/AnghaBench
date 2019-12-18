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
typedef  scalar_t__ uint32_t ;
struct ifdrv {int ifd_len; int /*<<< orphan*/  ifd_cmd; struct ifbrparam* ifd_data; int /*<<< orphan*/  ifd_name; } ;
struct ifbrparam {scalar_t__ ifbrp_ctime; } ;
struct bridge_if {scalar_t__ age_time; int /*<<< orphan*/  bif_name; } ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  b_param ;

/* Variables and functions */
 int /*<<< orphan*/  BRDGSTO ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SIOCSDRVSPEC ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifdrv*) ; 
 int /*<<< orphan*/  sock ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int
bridge_set_aging_time(struct bridge_if *bif, int32_t age_time)
{
	struct ifdrv ifd;
	struct ifbrparam b_param;

	strlcpy(ifd.ifd_name, bif->bif_name, IFNAMSIZ);
	ifd.ifd_len = sizeof(b_param);
	ifd.ifd_data = &b_param;
	b_param.ifbrp_ctime = (uint32_t) age_time;
	ifd.ifd_cmd = BRDGSTO;

	if (ioctl(sock, SIOCSDRVSPEC, &ifd) < 0) {
		syslog(LOG_ERR, "set bridge param: ioctl(BRDGSTO) "
		    "failed: %s", strerror(errno));
		return (-1);
	}

	bif->age_time = age_time;
	return (0);
}