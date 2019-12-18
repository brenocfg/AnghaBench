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
typedef  int u8 ;
typedef  int u16 ;
struct p2p_group_info {size_t num_clients; struct p2p_client_info* client; } ;
struct p2p_client_info {int const* p2p_device_addr; int const* p2p_interface_addr; int const* pri_dev_type; int num_sec_dev_types; int const* sec_dev_types; char const* dev_name; int dev_name_len; scalar_t__ config_methods; int /*<<< orphan*/  dev_capab; } ;

/* Variables and functions */
 scalar_t__ ATTR_DEV_NAME ; 
 int ETH_ALEN ; 
 size_t P2P_MAX_GROUP_ENTRIES ; 
 scalar_t__ WPA_GET_BE16 (int const*) ; 
 int WPS_DEV_NAME_MAX_LEN ; 
 int /*<<< orphan*/  os_memset (struct p2p_group_info*,int /*<<< orphan*/ ,int) ; 

int p2p_group_info_parse(const u8 *gi, size_t gi_len,
			 struct p2p_group_info *info)
{
	const u8 *g, *gend;

	os_memset(info, 0, sizeof(*info));
	if (gi == NULL)
		return 0;

	g = gi;
	gend = gi + gi_len;
	while (g < gend) {
		struct p2p_client_info *cli;
		const u8 *cend;
		u16 count;
		u8 len;

		cli = &info->client[info->num_clients];
		len = *g++;
		if (len > gend - g || len < 2 * ETH_ALEN + 1 + 2 + 8 + 1)
			return -1; /* invalid data */
		cend = g + len;
		/* g at start of P2P Client Info Descriptor */
		cli->p2p_device_addr = g;
		g += ETH_ALEN;
		cli->p2p_interface_addr = g;
		g += ETH_ALEN;
		cli->dev_capab = *g++;

		cli->config_methods = WPA_GET_BE16(g);
		g += 2;
		cli->pri_dev_type = g;
		g += 8;

		/* g at Number of Secondary Device Types */
		len = *g++;
		if (8 * len > cend - g)
			return -1; /* invalid data */
		cli->num_sec_dev_types = len;
		cli->sec_dev_types = g;
		g += 8 * len;

		/* g at Device Name in WPS TLV format */
		if (cend - g < 2 + 2)
			return -1; /* invalid data */
		if (WPA_GET_BE16(g) != ATTR_DEV_NAME)
			return -1; /* invalid Device Name TLV */
		g += 2;
		count = WPA_GET_BE16(g);
		g += 2;
		if (count > cend - g)
			return -1; /* invalid Device Name TLV */
		if (count >= WPS_DEV_NAME_MAX_LEN)
			count = WPS_DEV_NAME_MAX_LEN;
		cli->dev_name = (const char *) g;
		cli->dev_name_len = count;

		g = cend;

		info->num_clients++;
		if (info->num_clients == P2P_MAX_GROUP_ENTRIES)
			return -1;
	}

	return 0;
}