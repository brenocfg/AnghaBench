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
struct connection {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  out_packet_num; } ;

/* Variables and functions */
 TYPE_1__* RPCS_DATA (struct connection*) ; 
 int /*<<< orphan*/  prepare_rpc_query_raw (int /*<<< orphan*/ ,int*,int) ; 

void prepare_rpc_query (struct connection *c, int *q, int qn) {
  prepare_rpc_query_raw (RPCS_DATA(c)->out_packet_num++, q, qn);
}