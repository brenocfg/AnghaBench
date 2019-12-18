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
struct sfe_ipv6_connection_match {scalar_t__ match_src_port; scalar_t__ match_dest_port; scalar_t__ match_protocol; struct sfe_ipv6_connection_match* prev; struct sfe_ipv6_connection_match* next; struct net_device* match_dev; int /*<<< orphan*/  match_dest_ip; int /*<<< orphan*/  match_src_ip; } ;
struct sfe_ipv6_addr {int dummy; } ;
struct sfe_ipv6 {int /*<<< orphan*/  connection_match_hash_reorders; struct sfe_ipv6_connection_match** conn_match_hash; int /*<<< orphan*/  connection_match_hash_hits; } ;
struct net_device {int dummy; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 scalar_t__ sfe_ipv6_addr_equal (int /*<<< orphan*/ ,struct sfe_ipv6_addr*) ; 
 unsigned int sfe_ipv6_get_connection_match_hash (struct net_device*,scalar_t__,struct sfe_ipv6_addr*,scalar_t__,struct sfe_ipv6_addr*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sfe_ipv6_connection_match *
sfe_ipv6_find_connection_match(struct sfe_ipv6 *si, struct net_device *dev, u8 protocol,
					struct sfe_ipv6_addr *src_ip, __be16 src_port,
					struct sfe_ipv6_addr *dest_ip, __be16 dest_port)
{
	struct sfe_ipv6_connection_match *cm;
	struct sfe_ipv6_connection_match *head;
	unsigned int conn_match_idx;

	conn_match_idx = sfe_ipv6_get_connection_match_hash(dev, protocol, src_ip, src_port, dest_ip, dest_port);
	cm = si->conn_match_hash[conn_match_idx];

	/*
	 * If we don't have anything in this chain then bail.
	 */
	if (unlikely(!cm)) {
		return NULL;
	}

	/*
	 * Hopefully the first entry is the one we want.
	 */
	if ((cm->match_src_port == src_port)
	    && (cm->match_dest_port == dest_port)
	    && (sfe_ipv6_addr_equal(cm->match_src_ip, src_ip))
	    && (sfe_ipv6_addr_equal(cm->match_dest_ip, dest_ip))
	    && (cm->match_protocol == protocol)
	    && (cm->match_dev == dev)) {
		si->connection_match_hash_hits++;
		return cm;
	}

	/*
	 * Unfortunately we didn't find it at head, so we search it in chain and
	 * move matching entry to the top of the hash chain. We presume that this
	 * will be reused again very quickly.
	 */
	head = cm;
	do {
		cm = cm->next;
	} while (cm && (cm->match_src_port != src_port
		 || cm->match_dest_port != dest_port
		 || !sfe_ipv6_addr_equal(cm->match_src_ip, src_ip)
		 || !sfe_ipv6_addr_equal(cm->match_dest_ip, dest_ip)
		 || cm->match_protocol != protocol
		 || cm->match_dev != dev));

	/*
	 * Not found then we're done.
	 */
	if (unlikely(!cm)) {
		return NULL;
	}

	/*
	 * We found a match so move it.
	 */
	if (cm->next) {
		cm->next->prev = cm->prev;
	}
	cm->prev->next = cm->next;
	cm->prev = NULL;
	cm->next = head;
	head->prev = cm;
	si->conn_match_hash[conn_match_idx] = cm;
	si->connection_match_hash_reorders++;

	return cm;
}