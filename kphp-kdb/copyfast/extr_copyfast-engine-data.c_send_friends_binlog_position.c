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
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct relative {struct relative* next; TYPE_1__ node; } ;
struct connection {int dummy; } ;

/* Variables and functions */
 struct relative RELATIVES ; 
 struct connection* get_relative_connection (struct relative*) ; 
 int /*<<< orphan*/  rpc_send_binlog_info (struct connection*,int /*<<< orphan*/ ) ; 

void send_friends_binlog_position (void) {
  struct relative *cur = RELATIVES.next;
  while (cur != &RELATIVES) {
    struct connection *c = get_relative_connection (cur);
    if (c) {
      rpc_send_binlog_info (c, cur->node.id);
    }
    cur = cur->next;
  }
}