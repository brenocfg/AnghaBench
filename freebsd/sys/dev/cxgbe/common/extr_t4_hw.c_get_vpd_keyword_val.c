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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct t4_vpdr_hdr {int vpdr_tag; scalar_t__* vpdr_len; } ;
struct t4_vpd_hdr {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int VPD_INFO_FLD_HDR_SIZE ; 
 unsigned int VPD_LEN ; 
 scalar_t__ memcmp (scalar_t__ const*,char const*,int) ; 

__attribute__((used)) static int get_vpd_keyword_val(const u8 *vpd, const char *kw, int region)
{
	int i, tag;
	unsigned int offset, len;
	const struct t4_vpdr_hdr *vpdr;

	offset = sizeof(struct t4_vpd_hdr);
	vpdr = (const void *)(vpd + offset);
	tag = vpdr->vpdr_tag;
	len = (u16)vpdr->vpdr_len[0] + ((u16)vpdr->vpdr_len[1] << 8);
	while (region--) {
		offset += sizeof(struct t4_vpdr_hdr) + len;
		vpdr = (const void *)(vpd + offset);
		if (++tag != vpdr->vpdr_tag)
			return -ENOENT;
		len = (u16)vpdr->vpdr_len[0] + ((u16)vpdr->vpdr_len[1] << 8);
	}
	offset += sizeof(struct t4_vpdr_hdr);

	if (offset + len > VPD_LEN) {
		return -ENOENT;
	}

	for (i = offset; i + VPD_INFO_FLD_HDR_SIZE <= offset + len;) {
		if (memcmp(vpd + i , kw , 2) == 0){
			i += VPD_INFO_FLD_HDR_SIZE;
			return i;
		}

		i += VPD_INFO_FLD_HDR_SIZE + vpd[i+2];
	}

	return -ENOENT;
}