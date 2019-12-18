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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct rndis_pktinfo {int rm_size; int rm_pktinfooffset; void* rm_data; int rm_type; } ;
struct hn_rxinfo {int vlan_info; int csum_info; int hash_value; int hash_info; } ;

/* Variables and functions */
 int EINVAL ; 
 int HN_NDIS_HASH_INFO_INVALID ; 
 int HN_NDIS_HASH_INFO_SIZE ; 
 int HN_NDIS_HASH_VALUE_SIZE ; 
#define  HN_NDIS_PKTINFO_TYPE_HASHINF 131 
#define  HN_NDIS_PKTINFO_TYPE_HASHVAL 130 
 int HN_RXINFO_ALL ; 
 int HN_RXINFO_CSUM ; 
 int HN_RXINFO_HASHINF ; 
 int HN_RXINFO_HASHVAL ; 
 int HN_RXINFO_VLAN ; 
#define  NDIS_PKTINFO_TYPE_CSUM 129 
#define  NDIS_PKTINFO_TYPE_VLAN 128 
 int NDIS_RXCSUM_INFO_SIZE ; 
 int NDIS_VLAN_INFO_SIZE ; 
 int RNDIS_PKTINFO_SIZE_ALIGNMASK ; 
 scalar_t__ __predict_false (int) ; 

__attribute__((used)) static int
hn_rndis_rxinfo(const void *info_data, int info_dlen, struct hn_rxinfo *info)
{
	const struct rndis_pktinfo *pi = info_data;
	uint32_t mask = 0;

	while (info_dlen != 0) {
		const void *data;
		uint32_t dlen;

		if (__predict_false(info_dlen < sizeof(*pi)))
			return (EINVAL);
		if (__predict_false(info_dlen < pi->rm_size))
			return (EINVAL);
		info_dlen -= pi->rm_size;

		if (__predict_false(pi->rm_size & RNDIS_PKTINFO_SIZE_ALIGNMASK))
			return (EINVAL);
		if (__predict_false(pi->rm_size < pi->rm_pktinfooffset))
			return (EINVAL);
		dlen = pi->rm_size - pi->rm_pktinfooffset;
		data = pi->rm_data;

		switch (pi->rm_type) {
		case NDIS_PKTINFO_TYPE_VLAN:
			if (__predict_false(dlen < NDIS_VLAN_INFO_SIZE))
				return (EINVAL);
			info->vlan_info = *((const uint32_t *)data);
			mask |= HN_RXINFO_VLAN;
			break;

		case NDIS_PKTINFO_TYPE_CSUM:
			if (__predict_false(dlen < NDIS_RXCSUM_INFO_SIZE))
				return (EINVAL);
			info->csum_info = *((const uint32_t *)data);
			mask |= HN_RXINFO_CSUM;
			break;

		case HN_NDIS_PKTINFO_TYPE_HASHVAL:
			if (__predict_false(dlen < HN_NDIS_HASH_VALUE_SIZE))
				return (EINVAL);
			info->hash_value = *((const uint32_t *)data);
			mask |= HN_RXINFO_HASHVAL;
			break;

		case HN_NDIS_PKTINFO_TYPE_HASHINF:
			if (__predict_false(dlen < HN_NDIS_HASH_INFO_SIZE))
				return (EINVAL);
			info->hash_info = *((const uint32_t *)data);
			mask |= HN_RXINFO_HASHINF;
			break;

		default:
			goto next;
		}

		if (mask == HN_RXINFO_ALL) {
			/* All found; done */
			break;
		}
next:
		pi = (const struct rndis_pktinfo *)
		    ((const uint8_t *)pi + pi->rm_size);
	}

	/*
	 * Final fixup.
	 * - If there is no hash value, invalidate the hash info.
	 */
	if ((mask & HN_RXINFO_HASHVAL) == 0)
		info->hash_info = HN_NDIS_HASH_INFO_INVALID;
	return (0);
}