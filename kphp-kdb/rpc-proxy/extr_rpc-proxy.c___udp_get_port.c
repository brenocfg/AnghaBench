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
struct rpc_cluster_bucket {TYPE_1__* S; } ;
struct TYPE_2__ {int port; } ;

/* Variables and functions */

int __udp_get_port (struct rpc_cluster_bucket *B) {
  return B->S->port;
}