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
typedef  int /*<<< orphan*/  eloop_sock_handler ;
typedef  int /*<<< orphan*/  eloop_event_type ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct eloop_sock_table* eloop_get_sock_table (int /*<<< orphan*/ ) ; 
 int eloop_sock_table_add_sock (struct eloop_sock_table*,int,int /*<<< orphan*/ ,void*,void*) ; 

int eloop_register_sock(int sock, eloop_event_type type,
			eloop_sock_handler handler,
			void *eloop_data, void *user_data)
{
	struct eloop_sock_table *table;

	assert(sock >= 0);
	table = eloop_get_sock_table(type);
	return eloop_sock_table_add_sock(table, sock, handler,
					 eloop_data, user_data);
}