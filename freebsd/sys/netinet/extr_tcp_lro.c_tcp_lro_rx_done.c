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
struct lro_entry {int dummy; } ;
struct lro_ctrl {int /*<<< orphan*/  lro_active; } ;

/* Variables and functions */
 struct lro_entry* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_lro_active_remove (struct lro_entry*) ; 
 int /*<<< orphan*/  tcp_lro_flush (struct lro_ctrl*,struct lro_entry*) ; 

__attribute__((used)) static void
tcp_lro_rx_done(struct lro_ctrl *lc)
{
	struct lro_entry *le;

	while ((le = LIST_FIRST(&lc->lro_active)) != NULL) {
		tcp_lro_active_remove(le);
		tcp_lro_flush(lc, le);
	}
}