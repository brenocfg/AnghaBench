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
struct eap_sim_db_pending {struct eap_sim_db_pending* next; } ;
struct eap_sim_db_data {struct eap_sim_db_pending* pending; } ;

/* Variables and functions */

__attribute__((used)) static void eap_sim_db_add_pending(struct eap_sim_db_data *data,
				   struct eap_sim_db_pending *entry)
{
	entry->next = data->pending;
	data->pending = entry;
}