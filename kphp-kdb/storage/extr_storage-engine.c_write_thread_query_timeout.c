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
struct gather_data {int /*<<< orphan*/  key; int /*<<< orphan*/  key_len; } ;
struct conn_query {int dummy; } ;

/* Variables and functions */
 struct gather_data* GATHER_QUERY (struct conn_query*) ; 
 int /*<<< orphan*/  delete_write_thread_query (struct conn_query*) ; 
 int /*<<< orphan*/  gather_timeouts ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vkprintf (int,char*,struct conn_query*) ; 

int write_thread_query_timeout (struct conn_query *q) {
  vkprintf (3, "Query %p timeout.\n", q);
  struct gather_data *G = GATHER_QUERY(q);
  kprintf ("Query on key %.*s timeout\n", G->key_len, G->key);
  gather_timeouts++;
  delete_write_thread_query (q);
  return 0;
}