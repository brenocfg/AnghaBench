#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int idx; int /*<<< orphan*/  const* seq; } ;
struct TYPE_4__ {TYPE_1__ crypt; } ;
struct prism2_hostapd_param {TYPE_2__ u; int /*<<< orphan*/ * sta_addr; int /*<<< orphan*/  cmd; } ;
struct hostap_driver_data {int dummy; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  PRISM2_GET_ENCRYPTION ; 
 scalar_t__ hostapd_ioctl (struct hostap_driver_data*,struct prism2_hostapd_param*,size_t) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * os_zalloc (size_t) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int hostap_get_seqnum(const char *ifname, void *priv, const u8 *addr,
			     int idx, u8 *seq)
{
	struct hostap_driver_data *drv = priv;
	struct prism2_hostapd_param *param;
	u8 *buf;
	size_t blen;
	int ret = 0;

	blen = sizeof(*param) + 32;
	buf = os_zalloc(blen);
	if (buf == NULL)
		return -1;

	param = (struct prism2_hostapd_param *) buf;
	param->cmd = PRISM2_GET_ENCRYPTION;
	if (addr == NULL)
		os_memset(param->sta_addr, 0xff, ETH_ALEN);
	else
		os_memcpy(param->sta_addr, addr, ETH_ALEN);
	param->u.crypt.idx = idx;

	if (hostapd_ioctl(drv, param, blen)) {
		printf("Failed to get encryption.\n");
		ret = -1;
	} else {
		os_memcpy(seq, param->u.crypt.seq, 8);
	}
	os_free(buf);

	return ret;
}