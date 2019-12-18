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
struct sk_buff {scalar_t__ data; } ;
struct sfe_ipv6_udp_hdr {int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct sfe_ipv6_tcp_hdr {int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct sfe_ipv6_addr {int dummy; } ;
struct sfe_ipv6_ip_hdr {int version; int nexthdr; struct sfe_ipv6_addr daddr; struct sfe_ipv6_addr saddr; } ;
struct sfe_ipv6_frag_hdr {int /*<<< orphan*/  frag_off; } ;
struct sfe_ipv6_ext_hdr {unsigned int hdr_len; int next_hdr; } ;
struct sfe_ipv6_connection_match {struct sfe_ipv6_connection* connection; } ;
struct sfe_ipv6_connection {int dummy; } ;
struct sfe_ipv6 {int /*<<< orphan*/  lock; int /*<<< orphan*/  packets_not_forwarded; int /*<<< orphan*/ * exception_events; } ;
struct net_device {int dummy; } ;
struct icmp6hdr {scalar_t__ icmp6_type; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_TRACE (char*,...) ; 
 scalar_t__ ICMPV6_DEST_UNREACH ; 
 scalar_t__ ICMPV6_TIME_EXCEED ; 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 size_t SFE_IPV6_EXCEPTION_EVENT_HEADER_INCOMPLETE ; 
 size_t SFE_IPV6_EXCEPTION_EVENT_ICMP_FLUSHED_CONNECTION ; 
 size_t SFE_IPV6_EXCEPTION_EVENT_ICMP_HEADER_INCOMPLETE ; 
 size_t SFE_IPV6_EXCEPTION_EVENT_ICMP_IPV6_HEADER_INCOMPLETE ; 
 size_t SFE_IPV6_EXCEPTION_EVENT_ICMP_IPV6_NON_V6 ; 
 size_t SFE_IPV6_EXCEPTION_EVENT_ICMP_IPV6_UNHANDLED_PROTOCOL ; 
 size_t SFE_IPV6_EXCEPTION_EVENT_ICMP_NO_CONNECTION ; 
 size_t SFE_IPV6_EXCEPTION_EVENT_ICMP_UNHANDLED_TYPE ; 
 size_t SFE_IPV6_EXCEPTION_EVENT_NON_INITIAL_FRAGMENT ; 
 int SFE_IPV6_EXT_HDR_FRAG ; 
 unsigned int SFE_IPV6_FRAG_OFFSET ; 
 int /*<<< orphan*/  SFE_SYNC_REASON_FLUSH ; 
 unsigned int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,unsigned int) ; 
 struct sfe_ipv6_connection_match* sfe_ipv6_find_connection_match (struct sfe_ipv6*,struct net_device*,int,struct sfe_ipv6_addr*,int /*<<< orphan*/ ,struct sfe_ipv6_addr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfe_ipv6_flush_connection (struct sfe_ipv6*,struct sfe_ipv6_connection*,int /*<<< orphan*/ ) ; 
 int sfe_ipv6_is_ext_hdr (int) ; 
 int /*<<< orphan*/  sfe_ipv6_remove_connection (struct sfe_ipv6*,struct sfe_ipv6_connection*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int sfe_ipv6_recv_icmp(struct sfe_ipv6 *si, struct sk_buff *skb, struct net_device *dev,
			      unsigned int len, struct sfe_ipv6_ip_hdr *iph, unsigned int ihl)
{
	struct icmp6hdr *icmph;
	struct sfe_ipv6_ip_hdr *icmp_iph;
	struct sfe_ipv6_udp_hdr *icmp_udph;
	struct sfe_ipv6_tcp_hdr *icmp_tcph;
	struct sfe_ipv6_addr *src_ip;
	struct sfe_ipv6_addr *dest_ip;
	__be16 src_port;
	__be16 dest_port;
	struct sfe_ipv6_connection_match *cm;
	struct sfe_ipv6_connection *c;
	u8 next_hdr;

	/*
	 * Is our packet too short to contain a valid ICMP header?
	 */
	len -= ihl;
	if (!pskb_may_pull(skb, ihl + sizeof(struct icmp6hdr))) {
		spin_lock_bh(&si->lock);
		si->exception_events[SFE_IPV6_EXCEPTION_EVENT_ICMP_HEADER_INCOMPLETE]++;
		si->packets_not_forwarded++;
		spin_unlock_bh(&si->lock);

		DEBUG_TRACE("packet too short for ICMP header\n");
		return 0;
	}

	/*
	 * We only handle "destination unreachable" and "time exceeded" messages.
	 */
	icmph = (struct icmp6hdr *)(skb->data + ihl);
	if ((icmph->icmp6_type != ICMPV6_DEST_UNREACH)
	    && (icmph->icmp6_type != ICMPV6_TIME_EXCEED)) {
		spin_lock_bh(&si->lock);
		si->exception_events[SFE_IPV6_EXCEPTION_EVENT_ICMP_UNHANDLED_TYPE]++;
		si->packets_not_forwarded++;
		spin_unlock_bh(&si->lock);

		DEBUG_TRACE("unhandled ICMP type: 0x%x\n", icmph->icmp6_type);
		return 0;
	}

	/*
	 * Do we have the full embedded IP header?
	 * We should have 8 bytes of next L4 header - that's enough to identify
	 * the connection.
	 */
	len -= sizeof(struct icmp6hdr);
	ihl += sizeof(struct icmp6hdr);
	if (!pskb_may_pull(skb, ihl + sizeof(struct sfe_ipv6_ip_hdr) + sizeof(struct sfe_ipv6_ext_hdr))) {
		spin_lock_bh(&si->lock);
		si->exception_events[SFE_IPV6_EXCEPTION_EVENT_ICMP_IPV6_HEADER_INCOMPLETE]++;
		si->packets_not_forwarded++;
		spin_unlock_bh(&si->lock);

		DEBUG_TRACE("Embedded IP header not complete\n");
		return 0;
	}

	/*
	 * Is our embedded IP version wrong?
	 */
	icmp_iph = (struct sfe_ipv6_ip_hdr *)(icmph + 1);
	if (unlikely(icmp_iph->version != 6)) {
		spin_lock_bh(&si->lock);
		si->exception_events[SFE_IPV6_EXCEPTION_EVENT_ICMP_IPV6_NON_V6]++;
		si->packets_not_forwarded++;
		spin_unlock_bh(&si->lock);

		DEBUG_TRACE("IP version: %u\n", icmp_iph->version);
		return 0;
	}

	len -= sizeof(struct sfe_ipv6_ip_hdr);
	ihl += sizeof(struct sfe_ipv6_ip_hdr);
	next_hdr = icmp_iph->nexthdr;
	while (unlikely(sfe_ipv6_is_ext_hdr(next_hdr))) {
		struct sfe_ipv6_ext_hdr *ext_hdr;
		unsigned int ext_hdr_len;

		ext_hdr = (struct sfe_ipv6_ext_hdr *)(skb->data + ihl);
		if (next_hdr == SFE_IPV6_EXT_HDR_FRAG) {
			struct sfe_ipv6_frag_hdr *frag_hdr = (struct sfe_ipv6_frag_hdr *)ext_hdr;
			unsigned int frag_off = ntohs(frag_hdr->frag_off);

			if (frag_off & SFE_IPV6_FRAG_OFFSET) {
				spin_lock_bh(&si->lock);
				si->exception_events[SFE_IPV6_EXCEPTION_EVENT_NON_INITIAL_FRAGMENT]++;
				si->packets_not_forwarded++;
				spin_unlock_bh(&si->lock);

				DEBUG_TRACE("non-initial fragment\n");
				return 0;
			}
		}

		ext_hdr_len = ext_hdr->hdr_len;
		ext_hdr_len <<= 3;
		ext_hdr_len += sizeof(struct sfe_ipv6_ext_hdr);
		len -= ext_hdr_len;
		ihl += ext_hdr_len;
		/*
		 * We should have 8 bytes of next header - that's enough to identify
		 * the connection.
		 */
		if (!pskb_may_pull(skb, ihl + sizeof(struct sfe_ipv6_ext_hdr))) {
			spin_lock_bh(&si->lock);
			si->exception_events[SFE_IPV6_EXCEPTION_EVENT_HEADER_INCOMPLETE]++;
			si->packets_not_forwarded++;
			spin_unlock_bh(&si->lock);

			DEBUG_TRACE("extension header %d not completed\n", next_hdr);
			return 0;
		}

		next_hdr = ext_hdr->next_hdr;
	}

	/*
	 * Handle the embedded transport layer header.
	 */
	switch (next_hdr) {
	case IPPROTO_UDP:
		icmp_udph = (struct sfe_ipv6_udp_hdr *)(skb->data + ihl);
		src_port = icmp_udph->source;
		dest_port = icmp_udph->dest;
		break;

	case IPPROTO_TCP:
		icmp_tcph = (struct sfe_ipv6_tcp_hdr *)(skb->data + ihl);
		src_port = icmp_tcph->source;
		dest_port = icmp_tcph->dest;
		break;

	default:
		spin_lock_bh(&si->lock);
		si->exception_events[SFE_IPV6_EXCEPTION_EVENT_ICMP_IPV6_UNHANDLED_PROTOCOL]++;
		si->packets_not_forwarded++;
		spin_unlock_bh(&si->lock);

		DEBUG_TRACE("Unhandled embedded IP protocol: %u\n", next_hdr);
		return 0;
	}

	src_ip = &icmp_iph->saddr;
	dest_ip = &icmp_iph->daddr;

	spin_lock_bh(&si->lock);

	/*
	 * Look for a connection match.  Note that we reverse the source and destination
	 * here because our embedded message contains a packet that was sent in the
	 * opposite direction to the one in which we just received it.  It will have
	 * been sent on the interface from which we received it though so that's still
	 * ok to use.
	 */
	cm = sfe_ipv6_find_connection_match(si, dev, icmp_iph->nexthdr, dest_ip, dest_port, src_ip, src_port);
	if (unlikely(!cm)) {
		si->exception_events[SFE_IPV6_EXCEPTION_EVENT_ICMP_NO_CONNECTION]++;
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
	sfe_ipv6_remove_connection(si, c);
	si->exception_events[SFE_IPV6_EXCEPTION_EVENT_ICMP_FLUSHED_CONNECTION]++;
	si->packets_not_forwarded++;
	spin_unlock_bh(&si->lock);

	sfe_ipv6_flush_connection(si, c, SFE_SYNC_REASON_FLUSH);
	return 0;
}