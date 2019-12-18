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
typedef  int /*<<< orphan*/  php_worker ;
struct TYPE_3__ {int type; } ;
typedef  TYPE_1__ php_query_base_t ;
typedef  int /*<<< orphan*/  php_net_query_packet_t ;

/* Variables and functions */
#define  NETQ_PACKET 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_worker_run_net_query_packet (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void php_worker_run_net_query (php_worker *worker, php_query_base_t *q_base) {
  switch (q_base->type & 0xFFFF) {
    case NETQ_PACKET:
      php_worker_run_net_query_packet (worker, (php_net_query_packet_t *)q_base);
      break;
    default:
      assert ("unknown net_query type"&& 0);
  }
}