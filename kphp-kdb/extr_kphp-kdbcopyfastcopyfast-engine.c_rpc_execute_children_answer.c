#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rpc_children_answer {int children_num; int /*<<< orphan*/  children; } ;
struct node {int dummy; } ;
struct connection {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  children_received; } ;
struct TYPE_4__ {TYPE_1__ structured; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC ; 
 int MAX_CHILDREN ; 
 int /*<<< orphan*/  NODE_ID ; 
 TYPE_2__* STATS ; 
 int /*<<< orphan*/  clear_all_children_connections () ; 
 int /*<<< orphan*/  create_children_connections (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,int,...) ; 

int rpc_execute_children_answer (struct connection *c, struct rpc_children_answer *P, int len) {
  vkprintf (2, "rpc_execute_children_answer: len = %d, children_num = %d\n", len, P->children_num);
  if (len != sizeof (struct rpc_children_answer) + sizeof (struct node) * P->children_num) {
    return 0;
  }
  vkprintf (6, "%p %lld %d\n", CC, NODE_ID, P->children_num);
  STATS->structured.children_received++;
  clear_all_children_connections ();
  create_children_connections (P->children, (P->children_num > MAX_CHILDREN ? MAX_CHILDREN : P->children_num));
  return 0;
}