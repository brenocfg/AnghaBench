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
struct gas_query_pending {int /*<<< orphan*/  resp; int /*<<< orphan*/  adv_proto; int /*<<< orphan*/  req; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  dl_list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct gas_query_pending*) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gas_query_free(struct gas_query_pending *query, int del_list)
{
	if (del_list)
		dl_list_del(&query->list);

	wpabuf_free(query->req);
	wpabuf_free(query->adv_proto);
	wpabuf_free(query->resp);
	os_free(query);
}