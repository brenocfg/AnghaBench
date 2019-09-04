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
struct rpc_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpc_connection_tree ; 
 struct rpc_connection** tree_lookup_value_connection (int /*<<< orphan*/ ,void*) ; 

struct rpc_connection *rpc_connection_get (int fd) {
  struct rpc_connection **T = tree_lookup_value_connection (rpc_connection_tree, (void *)&fd);
  return T ? *T : 0;
}