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
typedef  int /*<<< orphan*/  ib_rpc_t ;
typedef  int /*<<< orphan*/  ib_rmpp_hdr_t ;
typedef  int /*<<< orphan*/  ib_portid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ibmp ; 
 int mad_send_via (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 

int mad_send(ib_rpc_t * rpc, ib_portid_t * dport, ib_rmpp_hdr_t * rmpp,
	     void *data)
{
	return mad_send_via(rpc, dport, rmpp, data, ibmp);
}