#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gas_query_pending {int /*<<< orphan*/  resp; int /*<<< orphan*/  adv_proto; int /*<<< orphan*/  req; int /*<<< orphan*/  list; struct gas_query* gas; } ;
struct gas_query {TYPE_1__* work; } ;
struct TYPE_2__ {struct gas_query_pending* ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  dl_list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct gas_query_pending*) ; 
 int /*<<< orphan*/  radio_work_done (TYPE_1__*) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gas_query_free(struct gas_query_pending *query, int del_list)
{
	struct gas_query *gas = query->gas;

	if (del_list)
		dl_list_del(&query->list);

	if (gas->work && gas->work->ctx == query) {
		radio_work_done(gas->work);
		gas->work = NULL;
	}

	wpabuf_free(query->req);
	wpabuf_free(query->adv_proto);
	wpabuf_free(query->resp);
	os_free(query);
}