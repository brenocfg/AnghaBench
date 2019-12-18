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
struct sfe_ipv6_connection_match {struct sfe_ipv6_connection_match* next; struct sfe_ipv6_connection_match* prev; int /*<<< orphan*/  match_dest_port; int /*<<< orphan*/  match_dest_ip; int /*<<< orphan*/  match_src_port; int /*<<< orphan*/  match_src_ip; int /*<<< orphan*/  match_protocol; int /*<<< orphan*/  match_dev; } ;
struct sfe_ipv6 {struct sfe_ipv6_connection_match** conn_match_hash; } ;

/* Variables and functions */
 unsigned int sfe_ipv6_get_connection_match_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void sfe_ipv6_insert_connection_match(struct sfe_ipv6 *si,
						    struct sfe_ipv6_connection_match *cm)
{
	struct sfe_ipv6_connection_match **hash_head;
	struct sfe_ipv6_connection_match *prev_head;
	unsigned int conn_match_idx
		= sfe_ipv6_get_connection_match_hash(cm->match_dev, cm->match_protocol,
						     cm->match_src_ip, cm->match_src_port,
						     cm->match_dest_ip, cm->match_dest_port);

	hash_head = &si->conn_match_hash[conn_match_idx];
	prev_head = *hash_head;
	cm->prev = NULL;
	if (prev_head) {
		prev_head->prev = cm;
	}

	cm->next = prev_head;
	*hash_head = cm;
}