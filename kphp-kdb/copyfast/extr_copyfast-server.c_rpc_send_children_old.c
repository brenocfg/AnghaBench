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
struct rpc_children_answer_old {int children_num; int /*<<< orphan*/  children; } ;
struct node {int dummy; } ;
struct connection {int dummy; } ;

/* Variables and functions */
 scalar_t__ Q ; 
 int /*<<< orphan*/  RPC_TYPE_CHILDREN_ANSWER_OLD ; 
 int /*<<< orphan*/  children_list ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int generate_children (long long) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rpc_create_query (struct rpc_children_answer_old*,int,struct connection*,int /*<<< orphan*/ ) ; 
 int rpc_send_query (struct rpc_children_answer_old*,struct connection*) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int rpc_send_children_old (struct connection *c, long long id) {
  if (verbosity >= 2) {
    fprintf (stderr, "rpc_send_children_old\n");
  }
  int x = generate_children (id);
  if (x < 0) {
    return 0;
  }
  struct rpc_children_answer_old *T = (struct rpc_children_answer_old *)Q;
  rpc_create_query (T, sizeof (struct rpc_children_answer_old) + x * sizeof (struct node), c, RPC_TYPE_CHILDREN_ANSWER_OLD);
  memcpy (T->children, children_list, x * sizeof (struct node));
  T->children_num = x;
  return rpc_send_query (T, c);
}