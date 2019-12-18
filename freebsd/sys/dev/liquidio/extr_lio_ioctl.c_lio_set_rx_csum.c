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
struct lio {int /*<<< orphan*/  oct_dev; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int IFCAP_LRO ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_RXCSUM_IPV6 ; 
 int /*<<< orphan*/  LIO_CMD_LRO_DISABLE ; 
 int LIO_LROIPV4 ; 
 int LIO_LROIPV6 ; 
 int if_getcapabilities (struct ifnet*) ; 
 int if_getcapenable (struct ifnet*) ; 
 struct lio* if_getsoftc (struct ifnet*) ; 
 int /*<<< orphan*/  if_togglecapenable (struct ifnet*,int) ; 
 int /*<<< orphan*/  lio_dev_info (int /*<<< orphan*/ ,char*) ; 
 int lio_set_feature (struct ifnet*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
lio_set_rx_csum(struct ifnet *ifp, uint32_t data)
{
	struct lio	*lio = if_getsoftc(ifp);
	int	ret = 0;

	if (if_getcapabilities(ifp) & (IFCAP_RXCSUM | IFCAP_RXCSUM_IPV6)) {
		if_togglecapenable(ifp, (IFCAP_RXCSUM | IFCAP_RXCSUM_IPV6));

		if (data) {
			/* LRO requires RXCSUM */
			if ((if_getcapabilities(ifp) & IFCAP_LRO) &&
			    (if_getcapenable(ifp) & IFCAP_LRO)) {
				ret = lio_set_feature(ifp, LIO_CMD_LRO_DISABLE,
						      LIO_LROIPV4 |
						      LIO_LROIPV6);
				if_togglecapenable(ifp, IFCAP_LRO);
			}
		}
	} else {
		lio_dev_info(lio->oct_dev, "Rx checksum offload capability not supported\n");
		return (ENODEV);
	}

	return ((ret) ? EINVAL : 0);
}