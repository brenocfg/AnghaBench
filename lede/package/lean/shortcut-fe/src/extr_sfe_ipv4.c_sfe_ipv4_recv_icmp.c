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
typedef  int u32 ;
struct sk_buff {scalar_t__ data; } ;
struct sfe_ipv4_udp_hdr {int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct sfe_ipv4_tcp_hdr {int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct sfe_ipv4_ip_hdr {int version; unsigned int ihl; int protocol; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct sfe_ipv4_connection_match {struct sfe_ipv4_connection* connection; } ;
struct sfe_ipv4_connection {int dummy; } ;
struct sfe_ipv4 {int /*<<< orphan*/  lock; int /*<<< orphan*/  packets_not_forwarded; int /*<<< orphan*/ * exception_events; } ;
struct net_device {int dummy; } ;
struct icmphdr {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_TRACE (char*,...) ; 
 scalar_t__ ICMP_DEST_UNREACH ; 
 scalar_t__ ICMP_TIME_EXCEEDED ; 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 size_t SFE_IPV4_EXCEPTION_EVENT_ICMP_FLUSHED_CONNECTION ; 
 size_t SFE_IPV4_EXCEPTION_EVENT_ICMP_HEADER_INCOMPLETE ; 
 size_t SFE_IPV4_EXCEPTION_EVENT_ICMP_IPV4_HEADER_INCOMPLETE ; 
 size_t SFE_IPV4_EXCEPTION_EVENT_ICMP_IPV4_IP_OPTIONS_INCOMPLETE ; 
 size_t SFE_IPV4_EXCEPTION_EVENT_ICMP_IPV4_NON_V4 ; 
 size_t SFE_IPV4_EXCEPTION_EVENT_ICMP_IPV4_TCP_HEADER_INCOMPLETE ; 
 size_t SFE_IPV4_EXCEPTION_EVENT_ICMP_IPV4_UDP_HEADER_INCOMPLETE ; 
 size_t SFE_IPV4_EXCEPTION_EVENT_ICMP_IPV4_UNHANDLED_PROTOCOL ; 
 size_t SFE_IPV4_EXCEPTION_EVENT_ICMP_NO_CONNECTION ; 
 size_t SFE_IPV4_EXCEPTION_EVENT_ICMP_UNHANDLED_TYPE ; 
 int /*<<< orphan*/  SFE_SYNC_REASON_FLUSH ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 struct sfe_ipv4_connection_match* sfe_ipv4_find_sfe_ipv4_connection_match (struct sfe_ipv4*,struct net_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfe_ipv4_flush_sfe_ipv4_connection (struct sfe_ipv4*,struct sfe_ipv4_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfe_ipv4_remove_sfe_ipv4_connection (struct sfe_ipv4*,struct sfe_ipv4_connection*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int sfe_ipv4_recv_icmp(struct sfe_ipv4 *si, struct sk_buff *skb, struct net_device *dev,
			      unsigned int len, struct sfe_ipv4_ip_hdr *iph, unsigned int ihl)
{
	struct icmphdr *icmph;
	struct sfe_ipv4_ip_hdr *icmp_iph;
	unsigned int icmp_ihl_words;
	unsigned int icmp_ihl;
	u32 *icmp_trans_h;
	struct sfe_ipv4_udp_hdr *icmp_udph;
	struct sfe_ipv4_tcp_hdr *icmp_tcph;
	__be32 src_ip;
	__be32 dest_ip;
	__be16 src_port;
	__be16 dest_port;
	struct sfe_ipv4_connection_match *cm;
	struct sfe_ipv4_connection *c;
	u32 pull_len = sizeof(struct icmphdr) + ihl;

	/*
	 * Is our packet too short to contain a valid ICMP header?
	 */
	len -= ihl;
	if (!pskb_may_pull(skb, pull_len)) {
		spin_lock_bh(&si->lock);
		si->exception_events[SFE_IPV4_EXCEPTION_EVENT_ICMP_HEADER_INCOMPLETE]++;
		si->packets_not_forwarded++;
		spin_unlock_bh(&si->lock);

		DEBUG_TRACE("packet too short for ICMP header\n");
		return 0;
	}

	/*
	 * We only handle "destination unreachable" and "time exceeded" messages.
	 */
	icmph = (struct icmphdr *)(skb->data + ihl);
	if ((icmph->type != ICMP_DEST_UNREACH)
	    && (icmph->type != ICMP_TIME_EXCEEDED)) {
		spin_lock_bh(&si->lock);
		si->exception_events[SFE_IPV4_EXCEPTION_EVENT_ICMP_UNHANDLED_TYPE]++;
		si->packets_not_forwarded++;
		spin_unlock_bh(&si->lock);

		DEBUG_TRACE("unhandled ICMP type: 0x%x\n", icmph->type);
		return 0;
	}

	/*
	 * Do we have the full embedded IP header?
	 */
	len -= sizeof(struct icmphdr);
	pull_len += sizeof(struct sfe_ipv4_ip_hdr);
	if (!pskb_may_pull(skb, pull_len)) {
		spin_lock_bh(&si->lock);
		si->exception_events[SFE_IPV4_EXCEPTION_EVENT_ICMP_IPV4_HEADER_INCOMPLETE]++;
		si->packets_not_forwarded++;
		spin_unlock_bh(&si->lock);

		DEBUG_TRACE("Embedded IP header not complete\n");
		return 0;
	}

	/*
	 * Is our embedded IP version wrong?
	 */
	icmp_iph = (struct sfe_ipv4_ip_hdr *)(icmph + 1);
	if (unlikely(icmp_iph->version != 4)) {
		spin_lock_bh(&si->lock);
		si->exception_events[SFE_IPV4_EXCEPTION_EVENT_ICMP_IPV4_NON_V4]++;
		si->packets_not_forwarded++;
		spin_unlock_bh(&si->lock);

		DEBUG_TRACE("IP version: %u\n", icmp_iph->version);
		return 0;
	}

	/*
	 * Do we have the full embedded IP header, including any options?
	 */
	icmp_ihl_words = icmp_iph->ihl;
	icmp_ihl = icmp_ihl_words << 2;
	pull_len += icmp_ihl - sizeof(struct sfe_ipv4_ip_hdr);
	if (!pskb_may_pull(skb, pull_len)) {
		spin_lock_bh(&si->lock);
		si->exception_events[SFE_IPV4_EXCEPTION_EVENT_ICMP_IPV4_IP_OPTIONS_INCOMPLETE]++;
		si->packets_not_forwarded++;
		spin_unlock_bh(&si->lock);

		DEBUG_TRACE("Embedded header not large enough for IP options\n");
		return 0;
	}

	len -= icmp_ihl;
	icmp_trans_h = ((u32 *)icmp_iph) + icmp_ihl_words;

	/*
	 * Handle the embedded transport layer header.
	 */
	switch (icmp_iph->protocol) {
	case IPPROTO_UDP:
		/*
		 * We should have 8 bytes of UDP header - that's enough to identify
		 * the connection.
		 */
		pull_len += 8;
		if (!pskb_may_pull(skb, pull_len)) {
			spin_lock_bh(&si->lock);
			si->exception_events[SFE_IPV4_EXCEPTION_EVENT_ICMP_IPV4_UDP_HEADER_INCOMPLETE]++;
			si->packets_not_forwarded++;
			spin_unlock_bh(&si->lock);

			DEBUG_TRACE("Incomplete embedded UDP header\n");
			return 0;
		}

		icmp_udph = (struct sfe_ipv4_udp_hdr *)icmp_trans_h;
		src_port = icmp_udph->source;
		dest_port = icmp_udph->dest;
		break;

	case IPPROTO_TCP:
		/*
		 * We should have 8 bytes of TCP header - that's enough to identify
		 * the connection.
		 */
		pull_len += 8;
		if (!pskb_may_pull(skb, pull_len)) {
			spin_lock_bh(&si->lock);
			si->exception_events[SFE_IPV4_EXCEPTION_EVENT_ICMP_IPV4_TCP_HEADER_INCOMPLETE]++;
			si->packets_not_forwarded++;
			spin_unlock_bh(&si->lock);

			DEBUG_TRACE("Incomplete embedded TCP header\n");
			return 0;
		}

		icmp_tcph = (struct sfe_ipv4_tcp_hdr *)icmp_trans_h;
		src_port = icmp_tcph->source;
		dest_port = icmp_tcph->dest;
		break;

	default:
		spin_lock_bh(&si->lock);
		si->exception_events[SFE_IPV4_EXCEPTION_EVENT_ICMP_IPV4_UNHANDLED_PROTOCOL]++;
		si->packets_not_forwarded++;
		spin_unlock_bh(&si->lock);

		DEBUG_TRACE("Unhandled embedded IP protocol: %u\n", icmp_iph->protocol);
		return 0;
	}

	src_ip = icmp_iph->saddr;
	dest_ip = icmp_iph->daddr;

	spin_lock_bh(&si->lock);

	/*
	 * Look for a connection match.  Note that we reverse the source and destination
	 * here because our embedded message contains a packet that was sent in the
	 * opposite direction to the one in which we just received it.  It will have
	 * been sent on the interface from which we received it though so that's still
	 * ok to use.
	 */
	cm = sfe_ipv4_find_sfe_ipv4_connection_match(si, dev, icmp_iph->protocol, dest_ip, dest_port, src_ip, src_port);
	if (unlikely(!cm)) {
		si->exception_events[SFE_IPV4_EXCEPTION_EVENT_ICMP_NO_CONNECTION]++;
		si->packets_not_forwarded++;
		spin_unlock_bh(&si->lock);

		DEBUG_TRACE("no connection found\n");
		return 0;
	}

	/*
	 * We found a connection so now remove it from the connection list and flush
	 * its state.
	 */
	c = cm->connection;
	sfe_ipv4_remove_sfe_ipv4_connection(si, c);
	si->exception_events[SFE_IPV4_EXCEPTION_EVENT_ICMP_FLUSHED_CONNECTION]++;
	si->packets_not_forwarded++;
	spin_unlock_bh(&si->lock);

	sfe_ipv4_flush_sfe_ipv4_connection(si, c, SFE_SYNC_REASON_FLUSH);
	return 0;
}