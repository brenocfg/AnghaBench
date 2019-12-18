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
struct ifbrparam {int /*<<< orphan*/  ifbrp_csize; } ;
struct bridge_if {int /*<<< orphan*/  max_addrs; int /*<<< orphan*/  bif_name; } ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  b_param ;

/* Variables and functions */
 int /*<<< orphan*/  BRDGSCACHE ; 
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
bridge_set_max_cache(struct bridge_if *bif, int32_t max_cache)
{
	struct ifdrv ifd;
	struct ifbrparam b_param;

	strlcpy(ifd.ifd_name, bif->bif_name, IFNAMSIZ);
	ifd.ifd_len = sizeof(b_param);
	ifd.ifd_data = &b_param;
	b_param.ifbrp_csize = max_cache;
	ifd.ifd_cmd = BRDGSCACHE;

	if (ioctl(sock, SIOCSDRVSPEC, &ifd) < 0) {
		syslog(LOG_ERR, "set bridge param: ioctl(BRDGSCACHE) "
		    "failed: %s", strerror(errno));
		return (-1);
	}

	bif->max_addrs = b_param.ifbrp_csize;
	return (0);
}