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
struct rpc_server {int dummy; } ;

/* Variables and functions */
 int last_server_fd ; 
 struct rpc_server** servers ; 

struct rpc_server *rpc_server_get (int fd) { /* {{{ */
  if (fd < 0 || fd >= last_server_fd) {
    return 0;
  }
  return servers[fd];
}