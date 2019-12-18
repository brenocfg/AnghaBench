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
struct p2ps_advertisement {struct p2ps_advertisement* next; } ;
struct p2p_data {struct p2ps_advertisement* p2ps_adv_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct p2ps_advertisement*) ; 
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*) ; 
 int /*<<< orphan*/  p2ps_prov_free (struct p2p_data*) ; 

void p2p_service_flush_asp(struct p2p_data *p2p)
{
	struct p2ps_advertisement *adv, *prev;

	if (!p2p)
		return;

	adv = p2p->p2ps_adv_list;
	while (adv) {
		prev = adv;
		adv = adv->next;
		os_free(prev);
	}

	p2p->p2ps_adv_list = NULL;
	p2ps_prov_free(p2p);
	p2p_dbg(p2p, "All ASP advertisements flushed");
}