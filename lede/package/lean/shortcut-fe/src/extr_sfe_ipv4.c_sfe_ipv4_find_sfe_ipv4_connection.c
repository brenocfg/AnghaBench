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
typedef  scalar_t__ u32 ;
struct sfe_ipv4_connection {scalar_t__ src_port; scalar_t__ dest_port; scalar_t__ src_ip; scalar_t__ dest_ip; scalar_t__ protocol; struct sfe_ipv4_connection* next; } ;
struct sfe_ipv4 {struct sfe_ipv4_connection** conn_hash; } ;
typedef  scalar_t__ __be32 ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 unsigned int sfe_ipv4_get_connection_hash (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline struct sfe_ipv4_connection *sfe_ipv4_find_sfe_ipv4_connection(struct sfe_ipv4 *si, u32 protocol,
									    __be32 src_ip, __be16 src_port,
									    __be32 dest_ip, __be16 dest_port)
{
	struct sfe_ipv4_connection *c;
	unsigned int conn_idx = sfe_ipv4_get_connection_hash(protocol, src_ip, src_port, dest_ip, dest_port);
	c = si->conn_hash[conn_idx];

	/*
	 * If we don't have anything in this chain then bale.
	 */
	if (unlikely(!c)) {
		return NULL;
	}

	/*
	 * Hopefully the first entry is the one we want.
	 */
	if ((c->src_port == src_port)
	    && (c->dest_port == dest_port)
	    && (c->src_ip == src_ip)
	    && (c->dest_ip == dest_ip)
	    && (c->protocol == protocol)) {
		return c;
	}

	/*
	 * Unfortunately we didn't find it at head, so we search it in chain.
	 */
	do {
		c = c->next;
	} while (c && (c->src_port != src_port
		 || c->dest_port != dest_port
		 || c->src_ip != src_ip
		 || c->dest_ip != dest_ip
		 || c->protocol != protocol));

	/*
	 * Will need connection entry for next create/destroy metadata,
	 * So no need to re-order entry for these requests
	 */
	return c;
}