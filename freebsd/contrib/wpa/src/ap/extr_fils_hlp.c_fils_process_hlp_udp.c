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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct udphdr {int /*<<< orphan*/  uh_sum; int /*<<< orphan*/  uh_ulen; int /*<<< orphan*/  uh_dport; int /*<<< orphan*/  uh_sport; } ;
struct sta_info {int dummy; } ;
struct iphdr {int dummy; } ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int DHCP_CLIENT_PORT ; 
 int DHCP_SERVER_PORT ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int fils_process_hlp_dhcp (struct hostapd_data*,struct sta_info*,int /*<<< orphan*/  const*,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,int,int,int) ; 

__attribute__((used)) static int fils_process_hlp_udp(struct hostapd_data *hapd,
				struct sta_info *sta, const u8 *dst,
				const u8 *pos, size_t len)
{
	const struct iphdr *iph;
	const struct udphdr *udph;
	u16 sport, dport, ulen;

	if (len < sizeof(*iph) + sizeof(*udph))
		return 0;
	iph = (const struct iphdr *) pos;
	udph = (const struct udphdr *) (iph + 1);
	sport = ntohs(udph->uh_sport);
	dport = ntohs(udph->uh_dport);
	ulen = ntohs(udph->uh_ulen);
	wpa_printf(MSG_DEBUG,
		   "FILS: HLP request UDP: sport=%u dport=%u ulen=%u sum=0x%x",
		   sport, dport, ulen, ntohs(udph->uh_sum));
	/* TODO: Check UDP checksum */
	if (ulen < sizeof(*udph) || ulen > len - sizeof(*iph))
		return 0;

	if (dport == DHCP_SERVER_PORT && sport == DHCP_CLIENT_PORT) {
		return fils_process_hlp_dhcp(hapd, sta, (const u8 *) (udph + 1),
					     ulen - sizeof(*udph));
	}

	return 0;
}