#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rsocket {TYPE_4__* cm_id; } ;
struct ib_connect_hdr {int dummy; } ;
struct TYPE_5__ {scalar_t__ sa_family; } ;
struct TYPE_6__ {TYPE_1__ src_addr; } ;
struct TYPE_7__ {TYPE_2__ addr; } ;
struct TYPE_8__ {TYPE_3__ route; } ;

/* Variables and functions */
 scalar_t__ AF_IB ; 

__attribute__((used)) static size_t rs_conn_data_offset(struct rsocket *rs)
{
	return (rs->cm_id->route.addr.src_addr.sa_family == AF_IB) ?
		sizeof(struct ib_connect_hdr) : 0;
}