#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sfe_ipv6_connection_match {TYPE_3__* active_prev; TYPE_3__* active_next; scalar_t__ active; TYPE_2__* prev; TYPE_1__* next; int /*<<< orphan*/  match_dest_port; int /*<<< orphan*/  match_dest_ip; int /*<<< orphan*/  match_src_port; int /*<<< orphan*/  match_src_ip; int /*<<< orphan*/  match_protocol; int /*<<< orphan*/  match_dev; } ;
struct sfe_ipv6 {TYPE_3__* active_tail; TYPE_3__* active_head; TYPE_1__** conn_match_hash; } ;
struct TYPE_6__ {struct TYPE_6__* active_prev; struct TYPE_6__* active_next; } ;
struct TYPE_5__ {TYPE_1__* next; } ;
struct TYPE_4__ {TYPE_2__* prev; } ;

/* Variables and functions */
 scalar_t__ likely (TYPE_3__*) ; 
 unsigned int sfe_ipv6_get_connection_match_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void sfe_ipv6_remove_connection_match(struct sfe_ipv6 *si, struct sfe_ipv6_connection_match *cm)
{
	/*
	 * Unlink the connection match entry from the hash.
	 */
	if (cm->prev) {
		cm->prev->next = cm->next;
	} else {
		unsigned int conn_match_idx
			= sfe_ipv6_get_connection_match_hash(cm->match_dev, cm->match_protocol,
							     cm->match_src_ip, cm->match_src_port,
							     cm->match_dest_ip, cm->match_dest_port);
		si->conn_match_hash[conn_match_idx] = cm->next;
	}

	if (cm->next) {
		cm->next->prev = cm->prev;
	}

	/*
	 * If the connection match entry is in the active list remove it.
	 */
	if (cm->active) {
		if (likely(cm->active_prev)) {
			cm->active_prev->active_next = cm->active_next;
		} else {
			si->active_head = cm->active_next;
		}

		if (likely(cm->active_next)) {
			cm->active_next->active_prev = cm->active_prev;
		} else {
			si->active_tail = cm->active_prev;
		}
	}
}