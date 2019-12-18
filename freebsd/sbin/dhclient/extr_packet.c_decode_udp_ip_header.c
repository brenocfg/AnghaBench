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
typedef  int u_int32_t ;
struct udphdr {int uh_sum; int /*<<< orphan*/  uh_sport; int /*<<< orphan*/  uh_ulen; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct ip {int /*<<< orphan*/  ip_src; int /*<<< orphan*/  ip_len; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int IPPROTO_UDP ; 
 int checksum (unsigned char*,int,int) ; 
 int /*<<< orphan*/  debug (char*,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  note (char*,int,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ wrapsum (int) ; 

ssize_t
decode_udp_ip_header(unsigned char *buf, int bufix, struct sockaddr_in *from,
    unsigned char *data, int buflen)
{
	struct ip *ip;
	struct udphdr *udp;
	u_int32_t ip_len = (buf[bufix] & 0xf) << 2;
	u_int32_t sum, usum;
	static int ip_packets_seen;
	static int ip_packets_bad_checksum;
	static int udp_packets_seen;
	static int udp_packets_bad_checksum;
	static int udp_packets_length_checked;
	static int udp_packets_length_overflow;
	int len = 0;

	ip = (struct ip *)(buf + bufix);
	udp = (struct udphdr *)(buf + bufix + ip_len);

	/* Check the IP header checksum - it should be zero. */
	ip_packets_seen++;
	if (wrapsum(checksum(buf + bufix, ip_len, 0)) != 0) {
		ip_packets_bad_checksum++;
		if (ip_packets_seen > 4 && ip_packets_bad_checksum != 0 &&
		    (ip_packets_seen / ip_packets_bad_checksum) < 2) {
			note("%d bad IP checksums seen in %d packets",
			    ip_packets_bad_checksum, ip_packets_seen);
			ip_packets_seen = ip_packets_bad_checksum = 0;
		}
		return (-1);
	}

	if (ntohs(ip->ip_len) != buflen)
		debug("ip length %d disagrees with bytes received %d.",
		    ntohs(ip->ip_len), buflen);

	memcpy(&from->sin_addr, &ip->ip_src, 4);

	/*
	 * Compute UDP checksums, including the ``pseudo-header'', the
	 * UDP header and the data.   If the UDP checksum field is zero,
	 * we're not supposed to do a checksum.
	 */
	if (!data) {
		data = buf + bufix + ip_len + sizeof(*udp);
		len = ntohs(udp->uh_ulen) - sizeof(*udp);
		udp_packets_length_checked++;
		if (len + data > buf + bufix + buflen) {
			udp_packets_length_overflow++;
			if (udp_packets_length_checked > 4 &&
			    (udp_packets_length_checked /
			    udp_packets_length_overflow) < 2) {
				note("%d udp packets in %d too long - dropped",
				    udp_packets_length_overflow,
				    udp_packets_length_checked);
				udp_packets_length_overflow =
				    udp_packets_length_checked = 0;
			}
			return (-1);
		}
		if (len + data != buf + bufix + buflen)
			debug("accepting packet with data after udp payload.");
	}

	usum = udp->uh_sum;
	udp->uh_sum = 0;

	sum = wrapsum(checksum((unsigned char *)udp, sizeof(*udp),
	    checksum(data, len, checksum((unsigned char *)&ip->ip_src,
	    2 * sizeof(ip->ip_src),
	    IPPROTO_UDP + (u_int32_t)ntohs(udp->uh_ulen)))));

	udp_packets_seen++;
	if (usum && usum != sum) {
		udp_packets_bad_checksum++;
		if (udp_packets_seen > 4 && udp_packets_bad_checksum != 0 &&
		    (udp_packets_seen / udp_packets_bad_checksum) < 2) {
			note("%d bad udp checksums in %d packets",
			    udp_packets_bad_checksum, udp_packets_seen);
			udp_packets_seen = udp_packets_bad_checksum = 0;
		}
		return (-1);
	}

	memcpy(&from->sin_port, &udp->uh_sport, sizeof(udp->uh_sport));

	return (ip_len + sizeof(*udp));
}