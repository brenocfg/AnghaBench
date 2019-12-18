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
struct tncs_data {struct tncs_data* next; scalar_t__ connectionID; int /*<<< orphan*/  imv; } ;
struct TYPE_2__ {struct tncs_data* connections; int /*<<< orphan*/  next_conn_id; int /*<<< orphan*/  imv; } ;

/* Variables and functions */
 struct tncs_data* os_zalloc (int) ; 
 TYPE_1__* tncs_global_data ; 

struct tncs_data * tncs_init(void)
{
	struct tncs_data *tncs;

	if (tncs_global_data == NULL)
		return NULL;

	tncs = os_zalloc(sizeof(*tncs));
	if (tncs == NULL)
		return NULL;
	tncs->imv = tncs_global_data->imv;
	tncs->connectionID = tncs_global_data->next_conn_id++;
	tncs->next = tncs_global_data->connections;
	tncs_global_data->connections = tncs;

	return tncs;
}