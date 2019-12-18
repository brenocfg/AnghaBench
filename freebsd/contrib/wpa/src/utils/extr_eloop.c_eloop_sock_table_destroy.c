#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct eloop_sock_table {int count; TYPE_1__* table; } ;
struct TYPE_3__ {int /*<<< orphan*/  handler; int /*<<< orphan*/  user_data; int /*<<< orphan*/  eloop_data; int /*<<< orphan*/  sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  os_free (TYPE_1__*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_trace_dump (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  wpa_trace_dump_funcname (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eloop_sock_table_destroy(struct eloop_sock_table *table)
{
	if (table) {
		int i;
		for (i = 0; i < table->count && table->table; i++) {
			wpa_printf(MSG_INFO, "ELOOP: remaining socket: "
				   "sock=%d eloop_data=%p user_data=%p "
				   "handler=%p",
				   table->table[i].sock,
				   table->table[i].eloop_data,
				   table->table[i].user_data,
				   table->table[i].handler);
			wpa_trace_dump_funcname("eloop unregistered socket "
						"handler",
						table->table[i].handler);
			wpa_trace_dump("eloop sock", &table->table[i]);
		}
		os_free(table->table);
	}
}