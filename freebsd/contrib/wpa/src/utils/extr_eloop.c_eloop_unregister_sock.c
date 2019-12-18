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
struct eloop_sock_table {int dummy; } ;
typedef  int /*<<< orphan*/  eloop_event_type ;

/* Variables and functions */
 struct eloop_sock_table* eloop_get_sock_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eloop_sock_table_remove_sock (struct eloop_sock_table*,int) ; 

void eloop_unregister_sock(int sock, eloop_event_type type)
{
	struct eloop_sock_table *table;

	table = eloop_get_sock_table(type);
	eloop_sock_table_remove_sock(table, sock);
}