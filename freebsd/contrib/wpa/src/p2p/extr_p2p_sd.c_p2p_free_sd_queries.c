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
struct p2p_sd_query {struct p2p_sd_query* next; } ;
struct p2p_data {scalar_t__ num_p2p_sd_queries; struct p2p_sd_query* sd_queries; } ;

/* Variables and functions */
 int /*<<< orphan*/  p2p_free_sd_query (struct p2p_sd_query*) ; 

void p2p_free_sd_queries(struct p2p_data *p2p)
{
	struct p2p_sd_query *q, *prev;
	q = p2p->sd_queries;
	p2p->sd_queries = NULL;
	while (q) {
		prev = q;
		q = q->next;
		p2p_free_sd_query(prev);
	}
	p2p->num_p2p_sd_queries = 0;
}