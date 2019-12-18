#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sfe_ipv6_connection {TYPE_4__* all_connections_prev; TYPE_3__* all_connections_next; TYPE_2__* prev; TYPE_1__* next; int /*<<< orphan*/  dest_port; int /*<<< orphan*/  dest_ip; int /*<<< orphan*/  src_port; int /*<<< orphan*/  src_ip; int /*<<< orphan*/  protocol; int /*<<< orphan*/  original_match; int /*<<< orphan*/  reply_match; } ;
struct sfe_ipv6 {int /*<<< orphan*/  num_connections; TYPE_4__* all_connections_tail; TYPE_3__* all_connections_head; TYPE_1__** conn_hash; } ;
struct TYPE_8__ {TYPE_3__* all_connections_next; } ;
struct TYPE_7__ {TYPE_4__* all_connections_prev; } ;
struct TYPE_6__ {TYPE_1__* next; } ;
struct TYPE_5__ {TYPE_2__* prev; } ;

/* Variables and functions */
 unsigned int sfe_ipv6_get_connection_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfe_ipv6_remove_connection_match (struct sfe_ipv6*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sfe_ipv6_remove_connection(struct sfe_ipv6 *si, struct sfe_ipv6_connection *c)
{
	/*
	 * Remove the connection match objects.
	 */
	sfe_ipv6_remove_connection_match(si, c->reply_match);
	sfe_ipv6_remove_connection_match(si, c->original_match);

	/*
	 * Unlink the connection.
	 */
	if (c->prev) {
		c->prev->next = c->next;
	} else {
		unsigned int conn_idx = sfe_ipv6_get_connection_hash(c->protocol, c->src_ip, c->src_port,
								     c->dest_ip, c->dest_port);
		si->conn_hash[conn_idx] = c->next;
	}

	if (c->next) {
		c->next->prev = c->prev;
	}

	/*
	 * Unlink connection from all_connections list
	 */
	if (c->all_connections_prev) {
		c->all_connections_prev->all_connections_next = c->all_connections_next;
	} else {
		si->all_connections_head = c->all_connections_next;
	}

	if (c->all_connections_next) {
		c->all_connections_next->all_connections_prev = c->all_connections_prev;
	} else {
		si->all_connections_tail = c->all_connections_prev;
	}

	si->num_connections--;
}