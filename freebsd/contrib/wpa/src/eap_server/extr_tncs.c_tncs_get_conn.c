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
struct tncs_data {scalar_t__ connectionID; struct tncs_data* next; } ;
struct TYPE_2__ {struct tncs_data* connections; } ;
typedef  scalar_t__ TNC_ConnectionID ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 TYPE_1__* tncs_global_data ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,unsigned long) ; 

__attribute__((used)) static struct tncs_data * tncs_get_conn(TNC_ConnectionID connectionID)
{
	struct tncs_data *tncs;

	if (tncs_global_data == NULL)
		return NULL;

	tncs = tncs_global_data->connections;
	while (tncs) {
		if (tncs->connectionID == connectionID)
			return tncs;
		tncs = tncs->next;
	}

	wpa_printf(MSG_DEBUG, "TNC: Connection ID %lu not found",
		   (unsigned long) connectionID);

	return NULL;
}